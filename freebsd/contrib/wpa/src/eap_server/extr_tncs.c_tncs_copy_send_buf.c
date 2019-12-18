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
typedef  int /*<<< orphan*/  u8 ;
struct tncs_data {int /*<<< orphan*/ * tncs_message; TYPE_1__* imv_data; } ;
struct TYPE_2__ {size_t imv_send_len; int /*<<< orphan*/ * imv_send; } ;

/* Variables and functions */
 int TNC_MAX_IMV_ID ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t os_strlen (int /*<<< orphan*/ *) ; 

u8 * tncs_copy_send_buf(struct tncs_data *tncs, u8 *pos)
{
	int i;

	for (i = 0; i < TNC_MAX_IMV_ID; i++) {
		if (tncs->imv_data[i].imv_send == NULL)
			continue;

		os_memcpy(pos, tncs->imv_data[i].imv_send,
			  tncs->imv_data[i].imv_send_len);
		pos += tncs->imv_data[i].imv_send_len;
		os_free(tncs->imv_data[i].imv_send);
		tncs->imv_data[i].imv_send = NULL;
		tncs->imv_data[i].imv_send_len = 0;
	}

	if (tncs->tncs_message) {
		size_t len = os_strlen(tncs->tncs_message);
		os_memcpy(pos, tncs->tncs_message, len);
		pos += len;
		os_free(tncs->tncs_message);
		tncs->tncs_message = NULL;
	}

	return pos;
}