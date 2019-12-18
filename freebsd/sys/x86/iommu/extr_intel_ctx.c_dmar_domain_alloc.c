#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dmar_unit {int hw_ecap; int /*<<< orphan*/  domids; } ;
struct dmar_domain {int domain; unsigned long long end; int agaw; int /*<<< orphan*/  flags; int /*<<< orphan*/  pgtbl_obj; struct dmar_unit* dmar; int /*<<< orphan*/  lock; int /*<<< orphan*/  unload_task; int /*<<< orphan*/  unload_entries; int /*<<< orphan*/  rb_root; int /*<<< orphan*/  contexts; } ;

/* Variables and functions */
 unsigned long long BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DMAR_DOMAIN_IDMAP ; 
 int DMAR_ECAP_PT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DMAR_DOMAIN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  Maxmem ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dmar_domain*) ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_domain_destroy (struct dmar_domain*) ; 
 int /*<<< orphan*/  dmar_domain_unload_task ; 
 int /*<<< orphan*/  dmar_gas_init_domain (struct dmar_domain*) ; 
 int dmar_gas_reserve_region (struct dmar_domain*,int,int) ; 
 int dmar_maxaddr2mgaw (struct dmar_unit*,unsigned long long,int) ; 
 int domain_alloc_pgtbl (struct dmar_domain*) ; 
 int /*<<< orphan*/  domain_get_idmap_pgtbl (struct dmar_domain*,unsigned long long) ; 
 int domain_set_agaw (struct dmar_domain*,int) ; 
 struct dmar_domain* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long long ptoa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dmar_domain *
dmar_domain_alloc(struct dmar_unit *dmar, bool id_mapped)
{
	struct dmar_domain *domain;
	int error, id, mgaw;

	id = alloc_unr(dmar->domids);
	if (id == -1)
		return (NULL);
	domain = malloc(sizeof(*domain), M_DMAR_DOMAIN, M_WAITOK | M_ZERO);
	domain->domain = id;
	LIST_INIT(&domain->contexts);
	RB_INIT(&domain->rb_root);
	TAILQ_INIT(&domain->unload_entries);
	TASK_INIT(&domain->unload_task, 0, dmar_domain_unload_task, domain);
	mtx_init(&domain->lock, "dmardom", NULL, MTX_DEF);
	domain->dmar = dmar;

	/*
	 * For now, use the maximal usable physical address of the
	 * installed memory to calculate the mgaw on id_mapped domain.
	 * It is useful for the identity mapping, and less so for the
	 * virtualized bus address space.
	 */
	domain->end = id_mapped ? ptoa(Maxmem) : BUS_SPACE_MAXADDR;
	mgaw = dmar_maxaddr2mgaw(dmar, domain->end, !id_mapped);
	error = domain_set_agaw(domain, mgaw);
	if (error != 0)
		goto fail;
	if (!id_mapped)
		/* Use all supported address space for remapping. */
		domain->end = 1ULL << (domain->agaw - 1);

	dmar_gas_init_domain(domain);

	if (id_mapped) {
		if ((dmar->hw_ecap & DMAR_ECAP_PT) == 0) {
			domain->pgtbl_obj = domain_get_idmap_pgtbl(domain,
			    domain->end);
		}
		domain->flags |= DMAR_DOMAIN_IDMAP;
	} else {
		error = domain_alloc_pgtbl(domain);
		if (error != 0)
			goto fail;
		/* Disable local apic region access */
		error = dmar_gas_reserve_region(domain, 0xfee00000,
		    0xfeefffff + 1);
		if (error != 0)
			goto fail;
	}
	return (domain);

fail:
	dmar_domain_destroy(domain);
	return (NULL);
}