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
struct tncs_data {TYPE_1__* imv_data; int /*<<< orphan*/  connectionID; struct tnc_if_imv* imv; } ;
struct tnc_if_imv {struct tnc_if_imv* next; } ;
struct TYPE_2__ {scalar_t__ imv_send_len; int /*<<< orphan*/ * imv_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  TNC_CONNECTION_STATE_CREATE ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_HANDSHAKE ; 
 int TNC_MAX_IMV_ID ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tncs_imv_notify_connection_change (struct tnc_if_imv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tncs_init_connection(struct tncs_data *tncs)
{
	struct tnc_if_imv *imv;
	int i;

	for (imv = tncs->imv; imv; imv = imv->next) {
		tncs_imv_notify_connection_change(
			imv, tncs->connectionID, TNC_CONNECTION_STATE_CREATE);
		tncs_imv_notify_connection_change(
			imv, tncs->connectionID,
			TNC_CONNECTION_STATE_HANDSHAKE);
	}

	for (i = 0; i < TNC_MAX_IMV_ID; i++) {
		os_free(tncs->imv_data[i].imv_send);
		tncs->imv_data[i].imv_send = NULL;
		tncs->imv_data[i].imv_send_len = 0;
	}
}