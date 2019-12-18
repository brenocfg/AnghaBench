#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tncs_data {struct tncs_data* tncs_message; struct tncs_data* next; TYPE_1__* imv_data; } ;
struct TYPE_4__ {struct tncs_data* connections; } ;
struct TYPE_3__ {struct tncs_data* imv_send; } ;

/* Variables and functions */
 int TNC_MAX_IMV_ID ; 
 int /*<<< orphan*/  os_free (struct tncs_data*) ; 
 TYPE_2__* tncs_global_data ; 

void tncs_deinit(struct tncs_data *tncs)
{
	int i;
	struct tncs_data *prev, *conn;

	if (tncs == NULL)
		return;

	for (i = 0; i < TNC_MAX_IMV_ID; i++)
		os_free(tncs->imv_data[i].imv_send);

	prev = NULL;
	conn = tncs_global_data->connections;
	while (conn) {
		if (conn == tncs) {
			if (prev)
				prev->next = tncs->next;
			else
				tncs_global_data->connections = tncs->next;
			break;
		}
		prev = conn;
		conn = conn->next;
	}

	os_free(tncs->tncs_message);
	os_free(tncs);
}