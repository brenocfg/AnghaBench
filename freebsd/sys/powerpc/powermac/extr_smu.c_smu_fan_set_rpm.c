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
struct TYPE_2__ {int /*<<< orphan*/  max_rpm; int /*<<< orphan*/  min_rpm; } ;
struct smu_fan {int old_style; int reg; int setpoint; TYPE_1__ fan; int /*<<< orphan*/  dev; } ;
struct smu_cmd {int len; int* data; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  SMU_FAN ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smu_fan_check_old_style (struct smu_fan*) ; 
 int smu_run_cmd (int /*<<< orphan*/ ,struct smu_cmd*,int) ; 

__attribute__((used)) static int
smu_fan_set_rpm(struct smu_fan *fan, int rpm)
{
	device_t smu = fan->dev;
	struct smu_cmd cmd;
	int error;

	cmd.cmd = SMU_FAN;
	error = EIO;

	/* Clamp to allowed range */
	rpm = max(fan->fan.min_rpm, rpm);
	rpm = min(fan->fan.max_rpm, rpm);

	smu_fan_check_old_style(fan);

	if (!fan->old_style) {
		cmd.len = 4;
		cmd.data[0] = 0x30;
		cmd.data[1] = fan->reg;
		cmd.data[2] = (rpm >> 8) & 0xff;
		cmd.data[3] = rpm & 0xff;

		error = smu_run_cmd(smu, &cmd, 1);
		if (error && error != EWOULDBLOCK)
			fan->old_style = 1;
	} else {
		cmd.len = 14;
		cmd.data[0] = 0x00; /* RPM fan. */
		cmd.data[1] = 1 << fan->reg;
		cmd.data[2 + 2*fan->reg] = (rpm >> 8) & 0xff;
		cmd.data[3 + 2*fan->reg] = rpm & 0xff;
		error = smu_run_cmd(smu, &cmd, 1);
	}

	if (error == 0)
		fan->setpoint = rpm;

	return (error);
}