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
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int ENOENT ; 
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_io_unmap_res (struct exca_softc*,struct resource*) ; 
 int /*<<< orphan*/  exca_mem_unmap_res (struct exca_softc*,struct resource*) ; 
 int rman_get_flags (struct resource*) ; 

int
exca_deactivate_resource(struct exca_softc *exca, device_t child, int type,
    int rid, struct resource *res)
{
	if (rman_get_flags(res) & RF_ACTIVE) { /* if activated */
		switch (type) {
		case SYS_RES_IOPORT:
			if (exca_io_unmap_res(exca, res))
				return (ENOENT);
			break;
		case SYS_RES_MEMORY:
			if (exca_mem_unmap_res(exca, res))
				return (ENOENT);
			break;
		}
	}
	return (BUS_DEACTIVATE_RESOURCE(device_get_parent(exca->dev), child,
	    type, rid, res));
}