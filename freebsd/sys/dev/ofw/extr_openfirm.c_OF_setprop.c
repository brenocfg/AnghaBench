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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int OFW_SETPROP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * ofw_def_impl ; 
 int /*<<< orphan*/  ofw_obj ; 

int
OF_setprop(phandle_t package, const char *propname, const void *buf, size_t len)
{

	if (ofw_def_impl == NULL)
		return (-1);

	return (OFW_SETPROP(ofw_obj, package, propname, buf,len));
}