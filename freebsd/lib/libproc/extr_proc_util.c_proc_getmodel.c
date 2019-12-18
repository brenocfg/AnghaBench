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
struct proc_handle {int model; } ;

/* Variables and functions */

int
proc_getmodel(struct proc_handle *phdl)
{

	if (phdl == NULL)
		return (-1);

	return (phdl->model);
}