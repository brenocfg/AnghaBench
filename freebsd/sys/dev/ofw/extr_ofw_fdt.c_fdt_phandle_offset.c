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
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 int fdt_off_dt_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtp ; 

__attribute__((used)) static int
fdt_phandle_offset(phandle_t p)
{
	int pint = (int)p;
	int dtoff = fdt_off_dt_struct(fdtp);

	if (pint < dtoff)
		return (-1);
	return (pint - dtoff);
}