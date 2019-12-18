#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  TYPE_2__* devclass_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * sysctl_tree; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; scalar_t__ nameunit; TYPE_2__* devclass; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  DEVICE_SYSCTL_DESC ; 
 int /*<<< orphan*/  DEVICE_SYSCTL_DRIVER ; 
 int /*<<< orphan*/  DEVICE_SYSCTL_LOCATION ; 
 int /*<<< orphan*/  DEVICE_SYSCTL_PARENT ; 
 int /*<<< orphan*/  DEVICE_SYSCTL_PNPINFO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE_WITH_LABEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 scalar_t__ bus_get_domain (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  devclass_sysctl_init (TYPE_2__*) ; 
 int /*<<< orphan*/  device_sysctl_handler ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
device_sysctl_init(device_t dev)
{
	devclass_t dc = dev->devclass;
	int domain;

	if (dev->sysctl_tree != NULL)
		return;
	devclass_sysctl_init(dc);
	sysctl_ctx_init(&dev->sysctl_ctx);
	dev->sysctl_tree = SYSCTL_ADD_NODE_WITH_LABEL(&dev->sysctl_ctx,
	    SYSCTL_CHILDREN(dc->sysctl_tree), OID_AUTO,
	    dev->nameunit + strlen(dc->name),
	    CTLFLAG_RD, NULL, "", "device_index");
	SYSCTL_ADD_PROC(&dev->sysctl_ctx, SYSCTL_CHILDREN(dev->sysctl_tree),
	    OID_AUTO, "%desc", CTLTYPE_STRING | CTLFLAG_RD,
	    dev, DEVICE_SYSCTL_DESC, device_sysctl_handler, "A",
	    "device description");
	SYSCTL_ADD_PROC(&dev->sysctl_ctx, SYSCTL_CHILDREN(dev->sysctl_tree),
	    OID_AUTO, "%driver", CTLTYPE_STRING | CTLFLAG_RD,
	    dev, DEVICE_SYSCTL_DRIVER, device_sysctl_handler, "A",
	    "device driver name");
	SYSCTL_ADD_PROC(&dev->sysctl_ctx, SYSCTL_CHILDREN(dev->sysctl_tree),
	    OID_AUTO, "%location", CTLTYPE_STRING | CTLFLAG_RD,
	    dev, DEVICE_SYSCTL_LOCATION, device_sysctl_handler, "A",
	    "device location relative to parent");
	SYSCTL_ADD_PROC(&dev->sysctl_ctx, SYSCTL_CHILDREN(dev->sysctl_tree),
	    OID_AUTO, "%pnpinfo", CTLTYPE_STRING | CTLFLAG_RD,
	    dev, DEVICE_SYSCTL_PNPINFO, device_sysctl_handler, "A",
	    "device identification");
	SYSCTL_ADD_PROC(&dev->sysctl_ctx, SYSCTL_CHILDREN(dev->sysctl_tree),
	    OID_AUTO, "%parent", CTLTYPE_STRING | CTLFLAG_RD,
	    dev, DEVICE_SYSCTL_PARENT, device_sysctl_handler, "A",
	    "parent device");
	if (bus_get_domain(dev, &domain) == 0)
		SYSCTL_ADD_INT(&dev->sysctl_ctx,
		    SYSCTL_CHILDREN(dev->sysctl_tree), OID_AUTO, "%domain",
		    CTLFLAG_RD, NULL, domain, "NUMA domain");
}