#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3c_iotimings {TYPE_1__* bank; } ;
struct s3c_cpufreq_config {int dummy; } ;
struct s3c2410_iobank_timing {int /*<<< orphan*/  bankcon; } ;
struct TYPE_2__ {struct s3c2410_iobank_timing* io_2410; } ;

/* Variables and functions */
 int MAX_BANKS ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bank_reg (int) ; 

void s3c2410_iotiming_set(struct s3c_cpufreq_config *cfg,
			  struct s3c_iotimings *iot)
{
	struct s3c2410_iobank_timing *bt;
	int bank;

	/* set the io timings from the specifier */

	for (bank = 0; bank < MAX_BANKS; bank++) {
		bt = iot->bank[bank].io_2410;
		if (!bt)
			continue;

		__raw_writel(bt->bankcon, bank_reg(bank));
	}
}