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
typedef  int /*<<< orphan*/  u_long ;
typedef  int phandle_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int OF_finddevice (char*) ; 
 scalar_t__ fdt_regsize (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ofw_bus_find_compatible (int,char*) ; 

__attribute__((used)) static int
alpine_get_cpu_resume_base(u_long *pbase, u_long *psize)
{
	phandle_t node;
	u_long base = 0;
	u_long size = 0;

	if (pbase == NULL || psize == NULL)
		return (EINVAL);

	if ((node = OF_finddevice("/")) == -1)
		return (EFAULT);

	if ((node =
	    ofw_bus_find_compatible(node, "annapurna-labs,al-cpu-resume")) == 0)
		return (EFAULT);

	if (fdt_regsize(node, &base, &size))
		return (EFAULT);

	*pbase = base;
	*psize = size;

	return (0);
}