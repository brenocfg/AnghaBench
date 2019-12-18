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
struct smu_cmd {int len; char* data; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_POWER ; 
 int /*<<< orphan*/  smu_run_cmd (int /*<<< orphan*/ ,struct smu_cmd*,int) ; 

__attribute__((used)) static void
smu_slew_cpu_voltage(device_t dev, int to)
{
	struct smu_cmd cmd;

	cmd.cmd = SMU_POWER;
	cmd.len = 8;
	cmd.data[0] = 'V';
	cmd.data[1] = 'S'; 
	cmd.data[2] = 'L'; 
	cmd.data[3] = 'E'; 
	cmd.data[4] = 'W'; 
	cmd.data[5] = 0xff;
	cmd.data[6] = 1;
	cmd.data[7] = to;

	smu_run_cmd(dev, &cmd, 1);
}