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
struct ssif_info {int got_alert; int data_len; int* multi_data; int* data; int multi_len; int multi_pos; int ssif_debug; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SMBUS_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_WRITE ; 
 int SSIF_DEBUG_MSG ; 
 int SSIF_IPMI_MULTI_PART_REQUEST_START ; 
 int SSIF_IPMI_REQUEST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_written_handler ; 
 int ssif_i2c_send (struct ssif_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_resend(struct ssif_info *ssif_info)
{
	int rv;
	int command;

	ssif_info->got_alert = false;

	if (ssif_info->data_len > 32) {
		command = SSIF_IPMI_MULTI_PART_REQUEST_START;
		ssif_info->multi_data = ssif_info->data;
		ssif_info->multi_len = ssif_info->data_len;
		/*
		 * Subtle thing, this is 32, not 33, because we will
		 * overwrite the thing at position 32 (which was just
		 * transmitted) with the new length.
		 */
		ssif_info->multi_pos = 32;
		ssif_info->data[0] = 32;
	} else {
		ssif_info->multi_data = NULL;
		command = SSIF_IPMI_REQUEST;
		ssif_info->data[0] = ssif_info->data_len;
	}

	rv = ssif_i2c_send(ssif_info, msg_written_handler, I2C_SMBUS_WRITE,
			  command, ssif_info->data, I2C_SMBUS_BLOCK_DATA);
	if (rv && (ssif_info->ssif_debug & SSIF_DEBUG_MSG))
		dev_dbg(&ssif_info->client->dev,
			"Error from i2c_non_blocking_op(4)\n");
	return rv;
}