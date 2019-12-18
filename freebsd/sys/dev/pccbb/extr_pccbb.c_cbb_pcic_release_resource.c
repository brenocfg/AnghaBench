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
struct cbb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int RF_ACTIVE ; 
 int bus_deactivate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  cbb_remove_res (struct cbb_softc*,struct resource*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_get_flags (struct resource*) ; 

__attribute__((used)) static int
cbb_pcic_release_resource(device_t brdev, device_t child, int type,
    int rid, struct resource *res)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	int error;

	if (rman_get_flags(res) & RF_ACTIVE) {
		error = bus_deactivate_resource(child, type, rid, res);
		if (error != 0)
			return (error);
	}
	cbb_remove_res(sc, res);
	return (BUS_RELEASE_RESOURCE(device_get_parent(brdev), child,
	    type, rid, res));
}