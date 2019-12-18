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
struct iwm_notif_wait_data {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_WAIT_LOCK_DESTROY (struct iwm_notif_wait_data*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct iwm_notif_wait_data*,int /*<<< orphan*/ ) ; 

void
iwm_notification_wait_free(struct iwm_notif_wait_data *notif_data)
{
	KASSERT(STAILQ_EMPTY(&notif_data->list), ("notif list isn't empty"));
	IWM_WAIT_LOCK_DESTROY(notif_data);
	free(notif_data, M_DEVBUF);
}