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
struct resource {int dummy; } ;
struct exca_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  PCCARD_WIDTH_AUTO ; 
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int exca_io_map (struct exca_softc*,int /*<<< orphan*/ ,struct resource*) ; 
 int exca_mem_map (struct exca_softc*,int /*<<< orphan*/ ,struct resource*) ; 
 int rman_get_flags (struct resource*) ; 

int
exca_activate_resource(struct exca_softc *exca, device_t child, int type,
    int rid, struct resource *res)
{
	int err;

	if (rman_get_flags(res) & RF_ACTIVE)
		return (0);
	err = BUS_ACTIVATE_RESOURCE(device_get_parent(exca->dev), child,
	    type, rid, res);
	if (err)
		return (err);
	switch (type) {
	case SYS_RES_IOPORT:
		err = exca_io_map(exca, PCCARD_WIDTH_AUTO, res);
		break;
	case SYS_RES_MEMORY:
		err = exca_mem_map(exca, 0, res);
		break;
	}
	if (err)
		BUS_DEACTIVATE_RESOURCE(device_get_parent(exca->dev), child,
		    type, rid, res);
	return (err);
}