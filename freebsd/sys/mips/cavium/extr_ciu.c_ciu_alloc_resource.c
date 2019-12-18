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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct ciu_softc {int /*<<< orphan*/  irq_rman; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  SYS_RES_IRQ 128 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ciu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct resource* rman_reserve_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
ciu_alloc_resource(device_t bus, device_t child, int type, int *rid,
		   rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource *res;
	struct ciu_softc *sc;
	
	sc = device_get_softc(bus);

	switch (type) {
	case SYS_RES_IRQ:
		break;
	default:
		return (bus_alloc_resource(device_get_parent(bus), type, rid,
					   start, end, count, flags));
	}

	/*
	 * One interrupt at a time for now.
	 */
	if (start != end)
		return (NULL);

	res = rman_reserve_resource(&sc->irq_rman, start, end, count, flags,
				    child);
	if (res != NULL)
		return (res);

	return (NULL);
}