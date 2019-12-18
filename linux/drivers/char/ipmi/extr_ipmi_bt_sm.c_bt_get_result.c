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
struct si_sm_data {int read_count; unsigned char* read_data; TYPE_1__* io; scalar_t__ truncated; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BT_DEBUG_MSG ; 
 unsigned char IPMI_ERR_MSG_TRUNCATED ; 
 int /*<<< orphan*/  IPMI_ERR_UNSPECIFIED ; 
 int IPMI_MAX_MSG_LENGTH ; 
 int bt_debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  force_result (struct si_sm_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static int bt_get_result(struct si_sm_data *bt,
			 unsigned char *data,
			 unsigned int length)
{
	int i, msg_len;

	msg_len = bt->read_count - 2;		/* account for length & seq */
	if (msg_len < 3 || msg_len > IPMI_MAX_MSG_LENGTH) {
		force_result(bt, IPMI_ERR_UNSPECIFIED);
		msg_len = 3;
	}
	data[0] = bt->read_data[1];
	data[1] = bt->read_data[3];
	if (length < msg_len || bt->truncated) {
		data[2] = IPMI_ERR_MSG_TRUNCATED;
		msg_len = 3;
	} else
		memcpy(data + 2, bt->read_data + 4, msg_len - 2);

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "result %d bytes:", msg_len);
		for (i = 0; i < msg_len; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	}
	return msg_len;
}