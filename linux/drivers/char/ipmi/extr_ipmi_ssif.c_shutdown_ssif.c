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
struct ssif_info {scalar_t__ ssif_state; int stopping; scalar_t__ thread; int /*<<< orphan*/  wake_thread; int /*<<< orphan*/  retry_timer; int /*<<< orphan*/  watch_timer; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SSIF_NORMAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_ssif_dev_attr_group ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 

__attribute__((used)) static void shutdown_ssif(void *send_info)
{
	struct ssif_info *ssif_info = send_info;

	device_remove_group(&ssif_info->client->dev, &ipmi_ssif_dev_attr_group);
	dev_set_drvdata(&ssif_info->client->dev, NULL);

	/* make sure the driver is not looking for flags any more. */
	while (ssif_info->ssif_state != SSIF_NORMAL)
		schedule_timeout(1);

	ssif_info->stopping = true;
	del_timer_sync(&ssif_info->watch_timer);
	del_timer_sync(&ssif_info->retry_timer);
	if (ssif_info->thread) {
		complete(&ssif_info->wake_thread);
		kthread_stop(ssif_info->thread);
	}
}