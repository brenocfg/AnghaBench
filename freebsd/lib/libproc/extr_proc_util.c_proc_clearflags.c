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
struct proc_handle {int flags; } ;

/* Variables and functions */
 int EINVAL ; 

int
proc_clearflags(struct proc_handle *phdl, int mask)
{

	if (phdl == NULL)
		return (EINVAL);

	phdl->flags &= ~mask;

	return (0);
}