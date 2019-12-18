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
struct sysc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysc_check_children (struct sysc*) ; 
 int sysc_check_registers (struct sysc*) ; 
 int sysc_ioremap (struct sysc*) ; 
 int sysc_parse_and_check_child_range (struct sysc*) ; 
 int sysc_parse_registers (struct sysc*) ; 

__attribute__((used)) static int sysc_map_and_check_registers(struct sysc *ddata)
{
	int error;

	error = sysc_parse_and_check_child_range(ddata);
	if (error)
		return error;

	sysc_check_children(ddata);

	error = sysc_parse_registers(ddata);
	if (error)
		return error;

	error = sysc_ioremap(ddata);
	if (error)
		return error;

	error = sysc_check_registers(ddata);
	if (error)
		return error;

	return 0;
}