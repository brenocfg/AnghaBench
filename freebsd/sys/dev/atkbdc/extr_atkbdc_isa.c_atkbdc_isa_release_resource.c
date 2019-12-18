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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct resource* irq; } ;
typedef  TYPE_1__ atkbdc_softc_t ;

/* Variables and functions */
 int KBDC_RID_KBD ; 
 int SYS_RES_IRQ ; 
 int bus_generic_rl_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbdc_isa_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	atkbdc_softc_t	*sc;
	
	sc = *(atkbdc_softc_t **)device_get_softc(dev);
	if (type == SYS_RES_IRQ && rid == KBDC_RID_KBD && r == sc->irq)
		return (0);
	return (bus_generic_rl_release_resource(dev, child, type, rid, r));
}