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
 long kvmppc_read_one_intr (int*) ; 
 scalar_t__ xive_enabled () ; 

long kvmppc_read_intr(void)
{
	long ret = 0;
	long rc;
	bool again;

	if (xive_enabled())
		return 1;

	do {
		again = false;
		rc = kvmppc_read_one_intr(&again);
		if (rc && (ret == 0 || rc > ret))
			ret = rc;
	} while (again);
	return ret;
}