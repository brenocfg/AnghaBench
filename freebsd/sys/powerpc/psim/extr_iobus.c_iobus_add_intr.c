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
typedef  int u_int ;
struct iobus_devinfo {int id_interrupt; int /*<<< orphan*/  id_resources; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  intr ;

/* Variables and functions */
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
iobus_add_intr(phandle_t devnode, struct iobus_devinfo *dinfo)
{
	u_int intr = -1;

	if (OF_getprop(devnode, "interrupt", &intr, sizeof(intr)) != -1) {
		resource_list_add(&dinfo->id_resources, 
				  SYS_RES_IRQ, 0, intr, intr, 1);
	}
	dinfo->id_interrupt = intr;
}