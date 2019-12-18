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
 int /*<<< orphan*/  H_INT_GET_QUEUE_INFO ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ plpar_busy_delay (long) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,unsigned long,long) ; 

__attribute__((used)) static long plpar_int_get_queue_info(unsigned long flags,
				     unsigned long target,
				     unsigned long priority,
				     unsigned long *esn_page,
				     unsigned long *esn_size)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	do {
		rc = plpar_hcall(H_INT_GET_QUEUE_INFO, retbuf, flags, target,
				 priority);
	} while (plpar_busy_delay(rc));

	if (rc) {
		pr_err("H_INT_GET_QUEUE_INFO cpu=%ld prio=%ld failed %ld\n",
		       target, priority, rc);
		return rc;
	}

	*esn_page = retbuf[0];
	*esn_size = retbuf[1];

	pr_devel("H_INT_GET_QUEUE_INFO page=%lx size=%lx\n",
		retbuf[0], retbuf[1]);

	return 0;
}