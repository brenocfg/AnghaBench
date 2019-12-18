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
struct rrm_data {int /*<<< orphan*/ * neighbor_rep_cb_ctx; int /*<<< orphan*/  (* notify_neighbor_rep ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpas_rrm_neighbor_rep_timeout_handler(void *data, void *user_ctx)
{
	struct rrm_data *rrm = data;

	if (!rrm->notify_neighbor_rep) {
		wpa_printf(MSG_ERROR,
			   "RRM: Unexpected neighbor report timeout");
		return;
	}

	wpa_printf(MSG_DEBUG, "RRM: Notifying neighbor report - NONE");
	rrm->notify_neighbor_rep(rrm->neighbor_rep_cb_ctx, NULL);

	rrm->notify_neighbor_rep = NULL;
	rrm->neighbor_rep_cb_ctx = NULL;
}