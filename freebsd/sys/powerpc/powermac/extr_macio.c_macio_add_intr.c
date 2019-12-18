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
struct macio_devinfo {int mdi_ninterrupts; int /*<<< orphan*/ * mdi_interrupts; int /*<<< orphan*/  mdi_resources; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  iparent ;
typedef  int /*<<< orphan*/  icells ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_IRQ (int,int) ; 
 scalar_t__ OF_getprop (int,char*,int*,int) ; 
 int OF_getprop_alloc_multi (int,char*,int,void**) ; 
 int OF_node_from_xref (int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
macio_add_intr(phandle_t devnode, struct macio_devinfo *dinfo)
{
	phandle_t iparent;
	int	*intr;
	int	i, nintr;
	int 	icells;

	if (dinfo->mdi_ninterrupts >= 6) {
		printf("macio: device has more than 6 interrupts\n");
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

	if (OF_getprop(OF_node_from_xref(iparent), "#interrupt-cells", &icells,
	    sizeof(icells)) <= 0)
		icells = 1;

	for (i = 0; i < nintr; i+=icells) {
		u_int irq = MAP_IRQ(iparent, intr[i]);

		resource_list_add(&dinfo->mdi_resources, SYS_RES_IRQ,
		    dinfo->mdi_ninterrupts, irq, irq, 1);

		dinfo->mdi_interrupts[dinfo->mdi_ninterrupts] = irq;
		dinfo->mdi_ninterrupts++;
	}
}