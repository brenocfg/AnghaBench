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
typedef  int u32 ;
struct altera_cvp_conf {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VSE_CVP_STATUS ; 
 int /*<<< orphan*/  altera_read_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int altera_cvp_wait_status(struct altera_cvp_conf *conf, u32 status_mask,
				  u32 status_val, int timeout_us)
{
	unsigned int retries;
	u32 val;

	retries = timeout_us / 10;
	if (timeout_us % 10)
		retries++;

	do {
		altera_read_config_dword(conf, VSE_CVP_STATUS, &val);
		if ((val & status_mask) == status_val)
			return 0;

		/* use small usleep value to re-check and break early */
		usleep_range(10, 11);
	} while (--retries);

	return -ETIMEDOUT;
}