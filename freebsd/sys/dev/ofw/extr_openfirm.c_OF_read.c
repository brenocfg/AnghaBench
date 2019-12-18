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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ihandle_t ;

/* Variables and functions */
 int OFW_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/ * ofw_def_impl ; 
 int /*<<< orphan*/  ofw_obj ; 

ssize_t
OF_read(ihandle_t instance, void *addr, size_t len)
{

	if (ofw_def_impl == NULL)
		return (-1);

	return (OFW_READ(ofw_obj, instance, addr, len));
}