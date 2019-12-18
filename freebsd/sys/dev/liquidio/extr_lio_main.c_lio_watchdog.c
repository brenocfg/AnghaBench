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
typedef  int uint16_t ;
struct octeon_device {int cores_crashed; int /*<<< orphan*/  watchdog_task; } ;
typedef  int /*<<< orphan*/  err_msg_was_printed ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_SLI_SCRATCH2 ; 
 int LIO_MAX_CORES ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  kproc_suspend_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int) ; 
 struct octeon_device* lio_get_other_octeon_device (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_ms_to_ticks (int) ; 
 scalar_t__ lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_watchdog(void *param)
{
	int		core_num;
	uint16_t	mask_of_crashed_or_stuck_cores = 0;
	struct octeon_device	*oct = param;
	bool		err_msg_was_printed[12];

	bzero(err_msg_was_printed, sizeof(err_msg_was_printed));

	while (1) {
		kproc_suspend_check(oct->watchdog_task);
		mask_of_crashed_or_stuck_cores =
			(uint16_t)lio_read_csr64(oct, LIO_CN23XX_SLI_SCRATCH2);

		if (mask_of_crashed_or_stuck_cores) {
			struct octeon_device *other_oct;

			oct->cores_crashed = true;
			other_oct = lio_get_other_octeon_device(oct);
			if (other_oct != NULL)
				other_oct->cores_crashed = true;

			for (core_num = 0; core_num < LIO_MAX_CORES;
			     core_num++) {
				bool core_crashed_or_got_stuck;

				core_crashed_or_got_stuck =
				    (mask_of_crashed_or_stuck_cores >>
				     core_num) & 1;
				if (core_crashed_or_got_stuck &&
				    !err_msg_was_printed[core_num]) {
					lio_dev_err(oct,
						    "ERROR: Octeon core %d crashed or got stuck! See oct-fwdump for details.\n",
						    core_num);
					err_msg_was_printed[core_num] = true;
				}
			}

		}

		/* sleep for two seconds */
		pause("-", lio_ms_to_ticks(2000));
	}
}