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
typedef  int /*<<< orphan*/  u32 ;
struct mthca_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;
struct mthca_dev {int dummy; } ;
struct mthca_adapter {int /*<<< orphan*/  board_id; int /*<<< orphan*/  inta_pin; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_QUERY_ADAPTER ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  MTHCA_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  QUERY_ADAPTER_DEVICE_ID_OFFSET ; 
 int /*<<< orphan*/  QUERY_ADAPTER_INTA_PIN_OFFSET ; 
 int /*<<< orphan*/  QUERY_ADAPTER_REVISION_ID_OFFSET ; 
 int /*<<< orphan*/  QUERY_ADAPTER_VENDOR_ID_OFFSET ; 
 int QUERY_ADAPTER_VSD_OFFSET ; 
 int /*<<< orphan*/  get_board_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd_box (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 

int mthca_QUERY_ADAPTER(struct mthca_dev *dev,
			struct mthca_adapter *adapter)
{
	struct mthca_mailbox *mailbox;
	u32 *outbox;
	int err;

#define QUERY_ADAPTER_OUT_SIZE             0x100
#define QUERY_ADAPTER_VENDOR_ID_OFFSET     0x00
#define QUERY_ADAPTER_DEVICE_ID_OFFSET     0x04
#define QUERY_ADAPTER_REVISION_ID_OFFSET   0x08
#define QUERY_ADAPTER_INTA_PIN_OFFSET      0x10
#define QUERY_ADAPTER_VSD_OFFSET           0x20

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_ADAPTER,
			    CMD_TIME_CLASS_A);

	if (err)
		goto out;

	if (!mthca_is_memfree(dev)) {
		MTHCA_GET(adapter->vendor_id, outbox,
			  QUERY_ADAPTER_VENDOR_ID_OFFSET);
		MTHCA_GET(adapter->device_id, outbox,
			  QUERY_ADAPTER_DEVICE_ID_OFFSET);
		MTHCA_GET(adapter->revision_id, outbox,
			  QUERY_ADAPTER_REVISION_ID_OFFSET);
	}
	MTHCA_GET(adapter->inta_pin, outbox,    QUERY_ADAPTER_INTA_PIN_OFFSET);

	get_board_id(outbox + QUERY_ADAPTER_VSD_OFFSET / 4,
		     adapter->board_id);

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}