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
struct sev_user_data_status {int /*<<< orphan*/  state; int /*<<< orphan*/  build; int /*<<< orphan*/  api_minor; int /*<<< orphan*/  api_major; } ;
struct TYPE_2__ {int /*<<< orphan*/  sev_state; int /*<<< orphan*/  build; int /*<<< orphan*/  api_minor; int /*<<< orphan*/  api_major; int /*<<< orphan*/  dev; struct sev_user_data_status status_cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* psp_master ; 
 int sev_platform_status (struct sev_user_data_status*,int*) ; 

__attribute__((used)) static int sev_get_api_version(void)
{
	struct sev_user_data_status *status;
	int error = 0, ret;

	status = &psp_master->status_cmd_buf;
	ret = sev_platform_status(status, &error);
	if (ret) {
		dev_err(psp_master->dev,
			"SEV: failed to get status. Error: %#x\n", error);
		return 1;
	}

	psp_master->api_major = status->api_major;
	psp_master->api_minor = status->api_minor;
	psp_master->build = status->build;
	psp_master->sev_state = status->state;

	return 0;
}