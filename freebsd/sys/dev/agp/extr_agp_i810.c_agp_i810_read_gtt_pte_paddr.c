#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct agp_i810_softc {TYPE_2__* match; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* read_gtt_pte ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int PAGE_MASK ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_paddr_t
agp_i810_read_gtt_pte_paddr(device_t dev, u_int index)
{
	struct agp_i810_softc *sc;
	u_int32_t pte;
	vm_paddr_t res;

	sc = device_get_softc(dev);
	pte = sc->match->driver->read_gtt_pte(dev, index);
	res = pte & ~PAGE_MASK;
	return (res);
}