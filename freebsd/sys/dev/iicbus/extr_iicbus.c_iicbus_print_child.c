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
struct iicbus_ivar {scalar_t__ addr; int /*<<< orphan*/  rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iicbus_ivar* IICBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
iicbus_print_child(device_t dev, device_t child)
{
	struct iicbus_ivar *devi = IICBUS_IVAR(child);
	int retval = 0;

	retval += bus_print_child_header(dev, child);
	if (devi->addr != 0)
		retval += printf(" at addr %#x", devi->addr);
	resource_list_print_type(&devi->rl, "irq", SYS_RES_IRQ, "%jd");
	retval += bus_print_child_footer(dev, child);

	return (retval);
}