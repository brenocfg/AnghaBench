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
typedef  int /*<<< orphan*/  ihandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFW_OPEN (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ofw_def_impl ; 
 int /*<<< orphan*/  ofw_obj ; 

ihandle_t
OF_open(const char *device)
{

	if (ofw_def_impl == NULL)
		return (0);

	return (OFW_OPEN(ofw_obj, device));
}