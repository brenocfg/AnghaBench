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
struct iwm_notification_wait {int dummy; } ;
struct iwm_notif_wait_data {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_WAIT_LOCK (struct iwm_notif_wait_data*) ; 
 int /*<<< orphan*/  IWM_WAIT_UNLOCK (struct iwm_notif_wait_data*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct iwm_notification_wait*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  iwm_notification_wait ; 

void
iwm_remove_notification(struct iwm_notif_wait_data *notif_data,
    struct iwm_notification_wait *wait_entry)
{
	IWM_WAIT_LOCK(notif_data);
	STAILQ_REMOVE(&notif_data->list, wait_entry, iwm_notification_wait,
	    entry);
	IWM_WAIT_UNLOCK(notif_data);
}