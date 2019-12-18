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
 int /*<<< orphan*/  H_INT_GET_SOURCE_CONFIG ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ plpar_busy_delay (long) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,long) ; 

__attribute__((used)) static long plpar_int_get_source_config(unsigned long flags,
					unsigned long lisn,
					unsigned long *target,
					unsigned long *prio,
					unsigned long *sw_irq)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	pr_devel("H_INT_GET_SOURCE_CONFIG flags=%lx lisn=%lx\n", flags, lisn);

	do {
		rc = plpar_hcall(H_INT_GET_SOURCE_CONFIG, retbuf, flags, lisn,
				 target, prio, sw_irq);
	} while (plpar_busy_delay(rc));

	if (rc) {
		pr_err("H_INT_GET_SOURCE_CONFIG lisn=%ld failed %ld\n",
		       lisn, rc);
		return rc;
	}

	*target = retbuf[0];
	*prio   = retbuf[1];
	*sw_irq = retbuf[2];

	pr_devel("H_INT_GET_SOURCE_CONFIG target=%lx prio=%lx sw_irq=%lx\n",
		retbuf[0], retbuf[1], retbuf[2]);

	return 0;
}