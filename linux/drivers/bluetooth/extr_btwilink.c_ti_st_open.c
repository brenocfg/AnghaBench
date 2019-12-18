#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ti_st {int reg_status; int /*<<< orphan*/ * st_write; int /*<<< orphan*/  wait_reg_completion; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * write; int /*<<< orphan*/  reg_complete_cb; int /*<<< orphan*/  recv; int /*<<< orphan*/  max_frame_size; struct ti_st* priv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int BT_REGISTER_TIMEOUT ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HCI_MAX_FRAME_SIZE ; 
 int MAX_BT_CHNL_IDS ; 
 struct ti_st* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  st_receive ; 
 int /*<<< orphan*/  st_reg_completion_cb ; 
 int st_register (TYPE_1__*) ; 
 int st_unregister (TYPE_1__*) ; 
 TYPE_1__* ti_st_proto ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_st_open(struct hci_dev *hdev)
{
	unsigned long timeleft;
	struct ti_st *hst;
	int err, i;

	BT_DBG("%s %p", hdev->name, hdev);

	/* provide contexts for callbacks from ST */
	hst = hci_get_drvdata(hdev);

	for (i = 0; i < MAX_BT_CHNL_IDS; i++) {
		ti_st_proto[i].priv_data = hst;
		ti_st_proto[i].max_frame_size = HCI_MAX_FRAME_SIZE;
		ti_st_proto[i].recv = st_receive;
		ti_st_proto[i].reg_complete_cb = st_reg_completion_cb;

		/* Prepare wait-for-completion handler */
		init_completion(&hst->wait_reg_completion);
		/* Reset ST registration callback status flag,
		 * this value will be updated in
		 * st_reg_completion_cb()
		 * function whenever it called from ST driver.
		 */
		hst->reg_status = -EINPROGRESS;

		err = st_register(&ti_st_proto[i]);
		if (!err)
			goto done;

		if (err != -EINPROGRESS) {
			BT_ERR("st_register failed %d", err);
			return err;
		}

		/* ST is busy with either protocol
		 * registration or firmware download.
		 */
		BT_DBG("waiting for registration "
				"completion signal from ST");
		timeleft = wait_for_completion_timeout
			(&hst->wait_reg_completion,
			 msecs_to_jiffies(BT_REGISTER_TIMEOUT));
		if (!timeleft) {
			BT_ERR("Timeout(%d sec),didn't get reg "
					"completion signal from ST",
					BT_REGISTER_TIMEOUT / 1000);
			return -ETIMEDOUT;
		}

		/* Is ST registration callback
		 * called with ERROR status?
		 */
		if (hst->reg_status != 0) {
			BT_ERR("ST registration completed with invalid "
					"status %d", hst->reg_status);
			return -EAGAIN;
		}

done:
		hst->st_write = ti_st_proto[i].write;
		if (!hst->st_write) {
			BT_ERR("undefined ST write function");
			for (i = 0; i < MAX_BT_CHNL_IDS; i++) {
				/* Undo registration with ST */
				err = st_unregister(&ti_st_proto[i]);
				if (err)
					BT_ERR("st_unregister() failed with "
							"error %d", err);
				hst->st_write = NULL;
			}
			return -EIO;
		}
	}
	return 0;
}