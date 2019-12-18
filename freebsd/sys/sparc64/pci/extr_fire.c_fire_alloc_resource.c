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
struct fire_softc {int /*<<< orphan*/  sc_ign; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTMAP_VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYS_RES_IRQ ; 
 struct fire_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct resource* ofw_pci_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
fire_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct fire_softc *sc;

	if (type == SYS_RES_IRQ && *rid == 0) {
		sc = device_get_softc(bus);
		start = end = INTMAP_VEC(sc->sc_ign, end);
	}
	return (ofw_pci_alloc_resource(bus, child, type, rid, start, end,
	    count, flags));
}