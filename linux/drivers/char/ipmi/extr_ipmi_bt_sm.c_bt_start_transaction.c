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
struct si_sm_data {scalar_t__ state; unsigned int* write_data; unsigned int write_count; int /*<<< orphan*/  BT_CAP_req2rsp; int /*<<< orphan*/  timeout; scalar_t__ truncated; scalar_t__ nonzero_status; scalar_t__ error_retries; int /*<<< orphan*/  seq; TYPE_1__* io; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BT_DEBUG_MSG ; 
 scalar_t__ BT_STATE_IDLE ; 
 scalar_t__ BT_STATE_LONG_BUSY ; 
 scalar_t__ BT_STATE_XACTION_START ; 
 int /*<<< orphan*/  IPMI_ERR_UNSPECIFIED ; 
 unsigned int IPMI_MAX_MSG_LENGTH ; 
 int IPMI_NODE_BUSY_ERR ; 
 int IPMI_NOT_IN_MY_STATE_ERR ; 
 int IPMI_REQ_LEN_EXCEEDED_ERR ; 
 int IPMI_REQ_LEN_INVALID_ERR ; 
 int bt_debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  force_result (struct si_sm_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static int bt_start_transaction(struct si_sm_data *bt,
				unsigned char *data,
				unsigned int size)
{
	unsigned int i;

	if (size < 2)
		return IPMI_REQ_LEN_INVALID_ERR;
	if (size > IPMI_MAX_MSG_LENGTH)
		return IPMI_REQ_LEN_EXCEEDED_ERR;

	if (bt->state == BT_STATE_LONG_BUSY)
		return IPMI_NODE_BUSY_ERR;

	if (bt->state != BT_STATE_IDLE)
		return IPMI_NOT_IN_MY_STATE_ERR;

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "+++++++++++++++++ New command\n");
		dev_dbg(bt->io->dev, "NetFn/LUN CMD [%d data]:", size - 2);
		for (i = 0; i < size; i ++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	}
	bt->write_data[0] = size + 1;	/* all data plus seq byte */
	bt->write_data[1] = *data;	/* NetFn/LUN */
	bt->write_data[2] = bt->seq++;
	memcpy(bt->write_data + 3, data + 1, size - 1);
	bt->write_count = size + 2;
	bt->error_retries = 0;
	bt->nonzero_status = 0;
	bt->truncated = 0;
	bt->state = BT_STATE_XACTION_START;
	bt->timeout = bt->BT_CAP_req2rsp;
	force_result(bt, IPMI_ERR_UNSPECIFIED);
	return 0;
}