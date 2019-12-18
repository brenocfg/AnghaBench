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
struct unin_chip_devinfo {int udi_ninterrupts; int /*<<< orphan*/ * udi_interrupts; int /*<<< orphan*/  udi_resources; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  iparent ;
typedef  int /*<<< orphan*/  icells ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  INTR_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  MAP_IRQ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 scalar_t__ OF_searchprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  powerpc_config_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
unin_chip_add_intr(phandle_t devnode, struct unin_chip_devinfo *dinfo)
{
	phandle_t iparent;
	int	*intr;
	int	i, nintr;
	int 	icells;

	if (dinfo->udi_ninterrupts >= 6) {
		printf("unin: device has more than 6 interrupts\n");
		return;
	}

	nintr = OF_getprop_alloc_multi(devnode, "interrupts", sizeof(*intr), 
		(void **)&intr);
	if (nintr == -1) {
		nintr = OF_getprop_alloc_multi(devnode, "AAPL,interrupts", 
			sizeof(*intr), (void **)&intr);
		if (nintr == -1)
			return;
	}

	if (intr[0] == -1)
		return;

	if (OF_getprop(devnode, "interrupt-parent", &iparent, sizeof(iparent))
	    <= 0)
		panic("Interrupt but no interrupt parent!\n");

	if (OF_searchprop(iparent, "#interrupt-cells", &icells, sizeof(icells))
	    <= 0)
		icells = 1;

	for (i = 0; i < nintr; i+=icells) {
		u_int irq = MAP_IRQ(iparent, intr[i]);

		resource_list_add(&dinfo->udi_resources, SYS_RES_IRQ,
		    dinfo->udi_ninterrupts, irq, irq, 1);

		if (icells > 1) {
			powerpc_config_intr(irq,
			    (intr[i+1] & 1) ? INTR_TRIGGER_LEVEL :
			    INTR_TRIGGER_EDGE, INTR_POLARITY_LOW);
		}

		dinfo->udi_interrupts[dinfo->udi_ninterrupts] = irq;
		dinfo->udi_ninterrupts++;
	}
}