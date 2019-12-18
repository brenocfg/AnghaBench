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
struct fw_dump {int dump_registered; int /*<<< orphan*/  ibm_configure_kernel_dump; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FADUMP_REGISTER ; 
 int /*<<< orphan*/  fdm ; 
 int /*<<< orphan*/  is_fadump_boot_mem_contiguous () ; 
 int /*<<< orphan*/  is_fadump_reserved_mem_contiguous () ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned int rtas_busy_delay_time (int) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtas_fadump_register(struct fw_dump *fadump_conf)
{
	unsigned int wait_time;
	int rc, err = -EIO;

	/* TODO: Add upper time limit for the delay */
	do {
		rc =  rtas_call(fadump_conf->ibm_configure_kernel_dump, 3, 1,
				NULL, FADUMP_REGISTER, &fdm,
				sizeof(struct rtas_fadump_mem_struct));

		wait_time = rtas_busy_delay_time(rc);
		if (wait_time)
			mdelay(wait_time);

	} while (wait_time);

	switch (rc) {
	case 0:
		pr_info("Registration is successful!\n");
		fadump_conf->dump_registered = 1;
		err = 0;
		break;
	case -1:
		pr_err("Failed to register. Hardware Error(%d).\n", rc);
		break;
	case -3:
		if (!is_fadump_boot_mem_contiguous())
			pr_err("Can't have holes in boot memory area.\n");
		else if (!is_fadump_reserved_mem_contiguous())
			pr_err("Can't have holes in reserved memory area.\n");

		pr_err("Failed to register. Parameter Error(%d).\n", rc);
		err = -EINVAL;
		break;
	case -9:
		pr_err("Already registered!\n");
		fadump_conf->dump_registered = 1;
		err = -EEXIST;
		break;
	default:
		pr_err("Failed to register. Unknown Error(%d).\n", rc);
		break;
	}

	return err;
}