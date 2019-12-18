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
struct timespec {int dummy; } ;
struct smu_cmd {int len; void** data; int /*<<< orphan*/  cmd; } ;
struct clocktime {scalar_t__ year; scalar_t__ mon; scalar_t__ day; scalar_t__ dow; scalar_t__ hour; scalar_t__ min; scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_RTC ; 
 void* SMU_RTC_SET ; 
 void* bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 int smu_run_cmd (int /*<<< orphan*/ ,struct smu_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smu_settime(device_t dev, struct timespec *ts)
{
	static struct smu_cmd cmd;
	struct clocktime ct;

	cmd.cmd = SMU_RTC;
	cmd.len = 8;
	cmd.data[0] = SMU_RTC_SET;

	clock_ts_to_ct(ts, &ct);

	cmd.data[1] = bin2bcd(ct.sec);
	cmd.data[2] = bin2bcd(ct.min);
	cmd.data[3] = bin2bcd(ct.hour);
	cmd.data[4] = bin2bcd(ct.dow);
	cmd.data[5] = bin2bcd(ct.day);
	cmd.data[6] = bin2bcd(ct.mon);
	cmd.data[7] = bin2bcd(ct.year - 2000);

	return (smu_run_cmd(dev, &cmd, 0));
}