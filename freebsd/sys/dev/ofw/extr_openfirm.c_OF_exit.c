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

/* Variables and functions */
 int /*<<< orphan*/  OFW_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ofw_def_impl ; 
 int /*<<< orphan*/  ofw_obj ; 
 int /*<<< orphan*/  panic (char*) ; 

void
OF_exit()
{

	if (ofw_def_impl == NULL)
		panic("OF_exit: Open Firmware not available");

	/* Should not return */
	OFW_EXIT(ofw_obj);

	for (;;)			/* just in case */
		;
}