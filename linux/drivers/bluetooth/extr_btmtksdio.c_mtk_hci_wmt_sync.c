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
typedef  int u32 ;
struct mtk_wmt_hdr {int dir; int op; int /*<<< orphan*/  flag; int /*<<< orphan*/  dlen; } ;
struct mtk_hci_wmt_cmd {int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;
struct btmtksdio_dev {TYPE_2__* evt_skb; int /*<<< orphan*/  tx_state; } ;
struct btmtk_hci_wmt_params {int dlen; int op; int* status; int /*<<< orphan*/  data; int /*<<< orphan*/  flag; } ;
struct btmtk_hci_wmt_evt_funcc {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int op; int flag; } ;
struct btmtk_hci_wmt_evt {TYPE_1__ whdr; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKSDIO_TX_WAIT_VND_EVT ; 
 int BTMTK_WMT_INVALID ; 
 int BTMTK_WMT_ON_DONE ; 
 int BTMTK_WMT_ON_PROGRESS ; 
 int BTMTK_WMT_ON_UNDONE ; 
 int BTMTK_WMT_PATCH_DONE ; 
 int BTMTK_WMT_PATCH_UNDONE ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
#define  MTK_WMT_FUNC_CTRL 129 
#define  MTK_WMT_SEMAPHORE 128 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __hci_cmd_send (struct hci_dev*,int,int,struct mtk_hci_wmt_cmd*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct btmtksdio_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hci_wmt_sync(struct hci_dev *hdev,
			    struct btmtk_hci_wmt_params *wmt_params)
{
	struct btmtksdio_dev *bdev = hci_get_drvdata(hdev);
	struct btmtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	u32 hlen, status = BTMTK_WMT_INVALID;
	struct btmtk_hci_wmt_evt *wmt_evt;
	struct mtk_hci_wmt_cmd wc;
	struct mtk_wmt_hdr *hdr;
	int err;

	hlen = sizeof(*hdr) + wmt_params->dlen;
	if (hlen > 255)
		return -EINVAL;

	hdr = (struct mtk_wmt_hdr *)&wc;
	hdr->dir = 1;
	hdr->op = wmt_params->op;
	hdr->dlen = cpu_to_le16(wmt_params->dlen + 1);
	hdr->flag = wmt_params->flag;
	memcpy(wc.data, wmt_params->data, wmt_params->dlen);

	set_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);

	err = __hci_cmd_send(hdev, 0xfc6f, hlen, &wc);
	if (err < 0) {
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		return err;
	}

	/* The vendor specific WMT commands are all answered by a vendor
	 * specific event and will not have the Command Status or Command
	 * Complete as with usual HCI command flow control.
	 *
	 * After sending the command, wait for BTMTKSDIO_TX_WAIT_VND_EVT
	 * state to be cleared. The driver specific event receive routine
	 * will clear that state and with that indicate completion of the
	 * WMT command.
	 */
	err = wait_on_bit_timeout(&bdev->tx_state, BTMTKSDIO_TX_WAIT_VND_EVT,
				  TASK_INTERRUPTIBLE, HCI_INIT_TIMEOUT);
	if (err == -EINTR) {
		bt_dev_err(hdev, "Execution of wmt command interrupted");
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		return err;
	}

	if (err) {
		bt_dev_err(hdev, "Execution of wmt command timed out");
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		return -ETIMEDOUT;
	}

	/* Parse and handle the return WMT event */
	wmt_evt = (struct btmtk_hci_wmt_evt *)bdev->evt_skb->data;
	if (wmt_evt->whdr.op != hdr->op) {
		bt_dev_err(hdev, "Wrong op received %d expected %d",
			   wmt_evt->whdr.op, hdr->op);
		err = -EIO;
		goto err_free_skb;
	}

	switch (wmt_evt->whdr.op) {
	case MTK_WMT_SEMAPHORE:
		if (wmt_evt->whdr.flag == 2)
			status = BTMTK_WMT_PATCH_UNDONE;
		else
			status = BTMTK_WMT_PATCH_DONE;
		break;
	case MTK_WMT_FUNC_CTRL:
		wmt_evt_funcc = (struct btmtk_hci_wmt_evt_funcc *)wmt_evt;
		if (be16_to_cpu(wmt_evt_funcc->status) == 0x404)
			status = BTMTK_WMT_ON_DONE;
		else if (be16_to_cpu(wmt_evt_funcc->status) == 0x420)
			status = BTMTK_WMT_ON_PROGRESS;
		else
			status = BTMTK_WMT_ON_UNDONE;
		break;
	}

	if (wmt_params->status)
		*wmt_params->status = status;

err_free_skb:
	kfree_skb(bdev->evt_skb);
	bdev->evt_skb = NULL;

	return err;
}