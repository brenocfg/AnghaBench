#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sf_buf {int dummy; } ;
struct dmar_unit {int unit; int hw_gcmd; int /*<<< orphan*/  segment; int /*<<< orphan*/  domains; } ;
struct dmar_domain {int /*<<< orphan*/  agaw; int /*<<< orphan*/  mgaw; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {int /*<<< orphan*/ * owner; } ;
struct dmar_ctx {int /*<<< orphan*/  refs; TYPE_1__ ctx_tag; struct dmar_domain* domain; } ;
typedef  int /*<<< orphan*/  dmar_ctx_entry_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int DMAR_GCMD_TE ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DMAR_CTX ; 
 int PCI_RID2BUS (int /*<<< orphan*/ ) ; 
 int PCI_RID2FUNC (int /*<<< orphan*/ ) ; 
 int PCI_RID2SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_PINNED_ASSERT ; 
 int /*<<< orphan*/  TD_PREP_PINNED_ASSERT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  ctx_id_entry_init (struct dmar_ctx*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctx_tag_init (struct dmar_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct dmar_ctx* dmar_ctx_alloc (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_ctx_link (struct dmar_ctx*) ; 
 struct dmar_domain* dmar_domain_alloc (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_domain_destroy (struct dmar_domain*) ; 
 int dmar_enable_translation (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_ensure_ctx_page (struct dmar_unit*,int) ; 
 struct dmar_ctx* dmar_find_ctx_locked (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int dmar_flush_for_ctx_entry (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_free_ctx_locked (struct dmar_unit*,struct dmar_ctx*) ; 
 int /*<<< orphan*/ * dmar_map_ctx_entry (struct dmar_ctx*,struct sf_buf**) ; 
 int /*<<< orphan*/  dmar_unmap_pgtbl (struct sf_buf*) ; 
 int domain_init_rmrr (struct dmar_domain*,int /*<<< orphan*/ *,int,int,int,int,int,void const*,int) ; 
 int /*<<< orphan*/  free (struct dmar_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int pci_get_bus (int /*<<< orphan*/ *) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 int pci_get_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static struct dmar_ctx *
dmar_get_ctx_for_dev1(struct dmar_unit *dmar, device_t dev, uint16_t rid,
    int dev_domain, int dev_busno, const void *dev_path, int dev_path_len,
    bool id_mapped, bool rmrr_init)
{
	struct dmar_domain *domain, *domain1;
	struct dmar_ctx *ctx, *ctx1;
	dmar_ctx_entry_t *ctxp;
	struct sf_buf *sf;
	int bus, slot, func, error;
	bool enable;

	if (dev != NULL) {
		bus = pci_get_bus(dev);
		slot = pci_get_slot(dev);
		func = pci_get_function(dev);
	} else {
		bus = PCI_RID2BUS(rid);
		slot = PCI_RID2SLOT(rid);
		func = PCI_RID2FUNC(rid);
	}
	enable = false;
	TD_PREP_PINNED_ASSERT;
	DMAR_LOCK(dmar);
	ctx = dmar_find_ctx_locked(dmar, rid);
	error = 0;
	if (ctx == NULL) {
		/*
		 * Perform the allocations which require sleep or have
		 * higher chance to succeed if the sleep is allowed.
		 */
		DMAR_UNLOCK(dmar);
		dmar_ensure_ctx_page(dmar, PCI_RID2BUS(rid));
		domain1 = dmar_domain_alloc(dmar, id_mapped);
		if (domain1 == NULL) {
			TD_PINNED_ASSERT;
			return (NULL);
		}
		if (!id_mapped) {
			error = domain_init_rmrr(domain1, dev, bus,
			    slot, func, dev_domain, dev_busno, dev_path,
			    dev_path_len);
			if (error != 0) {
				dmar_domain_destroy(domain1);
				TD_PINNED_ASSERT;
				return (NULL);
			}
		}
		ctx1 = dmar_ctx_alloc(domain1, rid);
		ctxp = dmar_map_ctx_entry(ctx1, &sf);
		DMAR_LOCK(dmar);

		/*
		 * Recheck the contexts, other thread might have
		 * already allocated needed one.
		 */
		ctx = dmar_find_ctx_locked(dmar, rid);
		if (ctx == NULL) {
			domain = domain1;
			ctx = ctx1;
			dmar_ctx_link(ctx);
			ctx->ctx_tag.owner = dev;
			ctx_tag_init(ctx, dev);

			/*
			 * This is the first activated context for the
			 * DMAR unit.  Enable the translation after
			 * everything is set up.
			 */
			if (LIST_EMPTY(&dmar->domains))
				enable = true;
			LIST_INSERT_HEAD(&dmar->domains, domain, link);
			ctx_id_entry_init(ctx, ctxp, false);
			if (dev != NULL) {
				device_printf(dev,
			    "dmar%d pci%d:%d:%d:%d rid %x domain %d mgaw %d "
				    "agaw %d %s-mapped\n",
				    dmar->unit, dmar->segment, bus, slot,
				    func, rid, domain->domain, domain->mgaw,
				    domain->agaw, id_mapped ? "id" : "re");
			}
			dmar_unmap_pgtbl(sf);
		} else {
			dmar_unmap_pgtbl(sf);
			dmar_domain_destroy(domain1);
			/* Nothing needs to be done to destroy ctx1. */
			free(ctx1, M_DMAR_CTX);
			domain = ctx->domain;
			ctx->refs++; /* tag referenced us */
		}
	} else {
		domain = ctx->domain;
		if (ctx->ctx_tag.owner == NULL)
			ctx->ctx_tag.owner = dev;
		ctx->refs++; /* tag referenced us */
	}

	error = dmar_flush_for_ctx_entry(dmar, enable);
	if (error != 0) {
		dmar_free_ctx_locked(dmar, ctx);
		TD_PINNED_ASSERT;
		return (NULL);
	}

	/*
	 * The dmar lock was potentially dropped between check for the
	 * empty context list and now.  Recheck the state of GCMD_TE
	 * to avoid unneeded command.
	 */
	if (enable && !rmrr_init && (dmar->hw_gcmd & DMAR_GCMD_TE) == 0) {
		error = dmar_enable_translation(dmar);
		if (error == 0) {
			if (bootverbose) {
				printf("dmar%d: enabled translation\n",
				    dmar->unit);
			}
		} else {
			printf("dmar%d: enabling translation failed, "
			    "error %d\n", dmar->unit, error);
			dmar_free_ctx_locked(dmar, ctx);
			TD_PINNED_ASSERT;
			return (NULL);
		}
	}
	DMAR_UNLOCK(dmar);
	TD_PINNED_ASSERT;
	return (ctx);
}