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
struct spibus_ivar {int cs; int mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct spibus_ivar* SPIBUS_IVAR (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 

__attribute__((used)) static int
spibus_print_child(device_t dev, device_t child)
{
	struct spibus_ivar *devi = SPIBUS_IVAR(child);
	int retval = 0;

	retval += bus_print_child_header(dev, child);
	retval += printf(" at cs %d", devi->cs);
	retval += printf(" mode %d", devi->mode);
	retval += bus_print_child_footer(dev, child);

	return (retval);
}