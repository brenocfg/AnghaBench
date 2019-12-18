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
typedef  size_t uint32_t ;
struct proc {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;
struct pmc_ownerhash {int dummy; } ;
struct pmc_owner {int /*<<< orphan*/  po_mtx; int /*<<< orphan*/  po_logbuffers; struct proc* po_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct pmc_ownerhash*,struct pmc_owner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_PMC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OWN ; 
 int /*<<< orphan*/  PMCDBG4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmc_owner*) ; 
 size_t PMC_HASH_PTR (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct pmc_owner* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 struct pmc_ownerhash* pmc_ownerhash ; 
 int /*<<< orphan*/  pmc_ownerhashmask ; 
 int /*<<< orphan*/  po_next ; 

__attribute__((used)) static struct pmc_owner *
pmc_allocate_owner_descriptor(struct proc *p)
{
	uint32_t hindex;
	struct pmc_owner *po;
	struct pmc_ownerhash *poh;

	hindex = PMC_HASH_PTR(p, pmc_ownerhashmask);
	poh = &pmc_ownerhash[hindex];

	/* allocate space for N pointers and one descriptor struct */
	po = malloc(sizeof(struct pmc_owner), M_PMC, M_WAITOK|M_ZERO);
	po->po_owner = p;
	LIST_INSERT_HEAD(poh, po, po_next); /* insert into hash table */

	TAILQ_INIT(&po->po_logbuffers);
	mtx_init(&po->po_mtx, "pmc-owner-mtx", "pmc-per-proc", MTX_SPIN);

	PMCDBG4(OWN,ALL,1, "allocate-owner proc=%p (%d, %s) pmc-owner=%p",
	    p, p->p_pid, p->p_comm, po);

	return po;
}