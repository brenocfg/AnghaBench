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
struct smu_cmd {int len; int* data; int /*<<< orphan*/  cmd; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MISC ; 
 int SMU_MISC_LED_CTRL ; 
 int /*<<< orphan*/  smu_run_cmd (void*,struct smu_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smu_set_sleepled(void *xdev, int onoff)
{
	static struct smu_cmd cmd;
	device_t smu = xdev;

	cmd.cmd = SMU_MISC;
	cmd.len = 3;
	cmd.data[0] = SMU_MISC_LED_CTRL;
	cmd.data[1] = 0;
	cmd.data[2] = onoff; 

	smu_run_cmd(smu, &cmd, 0);
}