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
struct sysc {scalar_t__* offsets; } ;
typedef  enum sysc_registers { ____Placeholder_sysc_registers } sysc_registers ;

/* Variables and functions */
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int sysc_show_reg(struct sysc *ddata,
			 char *bufp, enum sysc_registers reg)
{
	if (ddata->offsets[reg] < 0)
		return sprintf(bufp, ":NA");

	return sprintf(bufp, ":%x", ddata->offsets[reg]);
}