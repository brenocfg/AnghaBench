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
typedef  int /*<<< orphan*/  uint16_t ;
struct dmar_unit {int dummy; } ;
struct dmar_ctx {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DMAR_CTX_DISABLED ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int dmar_bus_dma_is_dev_disabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_free_ctx_locked (struct dmar_unit*,struct dmar_ctx*) ; 
 struct dmar_ctx* dmar_get_ctx_for_dev (struct dmar_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dmar_get_requester (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 

struct dmar_ctx *
dmar_instantiate_ctx(struct dmar_unit *dmar, device_t dev, bool rmrr)
{
	device_t requester;
	struct dmar_ctx *ctx;
	bool disabled;
	uint16_t rid;

	requester = dmar_get_requester(dev, &rid);

	/*
	 * If the user requested the IOMMU disabled for the device, we
	 * cannot disable the DMAR, due to possibility of other
	 * devices on the same DMAR still requiring translation.
	 * Instead provide the identity mapping for the device
	 * context.
	 */
	disabled = dmar_bus_dma_is_dev_disabled(pci_get_domain(requester), 
	    pci_get_bus(requester), pci_get_slot(requester), 
	    pci_get_function(requester));
	ctx = dmar_get_ctx_for_dev(dmar, requester, rid, disabled, rmrr);
	if (ctx == NULL)
		return (NULL);
	if (disabled) {
		/*
		 * Keep the first reference on context, release the
		 * later refs.
		 */
		DMAR_LOCK(dmar);
		if ((ctx->flags & DMAR_CTX_DISABLED) == 0) {
			ctx->flags |= DMAR_CTX_DISABLED;
			DMAR_UNLOCK(dmar);
		} else {
			dmar_free_ctx_locked(dmar, ctx);
		}
		ctx = NULL;
	}
	return (ctx);
}