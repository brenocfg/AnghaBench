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
struct rtas_fadump_mem_struct {int dummy; } ;
struct fw_dump {scalar_t__ dump_registered; int /*<<< orphan*/  ibm_configure_kernel_dump; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FADUMP_UNREGISTER ; 
 int /*<<< orphan*/  fdm ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 unsigned int rtas_busy_delay_time (int) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtas_fadump_unregister(struct fw_dump *fadump_conf)
{
	unsigned int wait_time;
	int rc;

	/* TODO: Add upper time limit for the delay */
	do {
		rc =  rtas_call(fadump_conf->ibm_configure_kernel_dump, 3, 1,
				NULL, FADUMP_UNREGISTER, &fdm,
				sizeof(struct rtas_fadump_mem_struct));

		wait_time = rtas_busy_delay_time(rc);
		if (wait_time)
			mdelay(wait_time);
	} while (wait_time);

	if (rc) {
		pr_err("Failed to un-register - unexpected error(%d).\n", rc);
		return -EIO;
	}

	fadump_conf->dump_registered = 0;
	return 0;
}