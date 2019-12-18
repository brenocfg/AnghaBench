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
struct nvme_controller_data {int npss; int /*<<< orphan*/ * power_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_list_one (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
power_list(struct nvme_controller_data *cdata)
{
	int i;

	printf("\nPower States Supported: %d\n\n", cdata->npss + 1);
	printf(" #   Max pwr  Enter Lat  Exit Lat RT RL WT WL Idle Pwr  Act Pwr Workloadd\n");
	printf("--  --------  --------- --------- -- -- -- -- -------- -------- --\n");
	for (i = 0; i <= cdata->npss; i++)
		power_list_one(i, &cdata->power_state[i]);
}