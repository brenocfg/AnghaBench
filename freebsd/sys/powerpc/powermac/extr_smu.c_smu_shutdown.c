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
struct smu_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;
typedef  void* device_t ;

/* Variables and functions */
 int RB_HALT ; 
 int /*<<< orphan*/  SMU_POWER ; 
 int /*<<< orphan*/  smu_run_cmd (void*,struct smu_cmd*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smu_shutdown(void *xdev, int howto)
{
	device_t smu = xdev;
	struct smu_cmd cmd;

	cmd.cmd = SMU_POWER;
	if (howto & RB_HALT)
		strcpy(cmd.data, "SHUTDOWN");
	else
		strcpy(cmd.data, "RESTART");

	cmd.len = strlen(cmd.data);

	smu_run_cmd(smu, &cmd, 1);

	for (;;);
}