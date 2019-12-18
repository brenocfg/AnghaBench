#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  TYPE_1__* if_irq_t ;
typedef  TYPE_2__* if_ctx_t ;
typedef  int /*<<< orphan*/ * driver_intr_t ;
typedef  int /*<<< orphan*/ * driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int ifc_flags; int /*<<< orphan*/  ifc_dev; } ;
struct TYPE_5__ {void* ii_tag; struct resource* ii_res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IFC_LEGACY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,struct resource*,void*,char*,char const*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char const*,...) ; 

__attribute__((used)) static int
_iflib_irq_alloc(if_ctx_t ctx, if_irq_t irq, int rid,
		 driver_filter_t filter, driver_intr_t handler, void *arg,
		 const char *name)
{
	struct resource *res;
	void *tag = NULL;
	device_t dev = ctx->ifc_dev;
	int flags, i, rc;

	flags = RF_ACTIVE;
	if (ctx->ifc_flags & IFC_LEGACY)
		flags |= RF_SHAREABLE;
	MPASS(rid < 512);
	i = rid;
	res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &i, flags);
	if (res == NULL) {
		device_printf(dev,
		    "failed to allocate IRQ for rid %d, name %s.\n", rid, name);
		return (ENOMEM);
	}
	irq->ii_res = res;
	KASSERT(filter == NULL || handler == NULL, ("filter and handler can't both be non-NULL"));
	rc = bus_setup_intr(dev, res, INTR_MPSAFE | INTR_TYPE_NET,
						filter, handler, arg, &tag);
	if (rc != 0) {
		device_printf(dev,
		    "failed to setup interrupt for rid %d, name %s: %d\n",
					  rid, name ? name : "unknown", rc);
		return (rc);
	} else if (name)
		bus_describe_intr(dev, res, tag, "%s", name);

	irq->ii_tag = tag;
	return (0);
}