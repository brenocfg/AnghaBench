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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  superio_dev_type_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* devtype_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,char*,int) ; 
 int superio_get_ldn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_get_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
superio_print_child(device_t parent, device_t child)
{
	superio_dev_type_t type;
	uint8_t ldn;
	int retval;

	ldn = superio_get_ldn(child);
	type = superio_get_type(child);

	retval = bus_print_child_header(parent, child);
	retval += printf(" at %s ldn 0x%02x", devtype_to_str(type), ldn);
	retval += bus_print_child_footer(parent, child);

	return (retval);
}