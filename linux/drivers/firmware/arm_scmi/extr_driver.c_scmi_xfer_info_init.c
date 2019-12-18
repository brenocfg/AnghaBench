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
typedef  int /*<<< orphan*/  u8 ;
struct scmi_xfers_info {int /*<<< orphan*/  xfer_lock; struct scmi_xfer* xfer_block; void* xfer_alloc_table; } ;
struct TYPE_4__ {void* buf; } ;
struct TYPE_3__ {void* buf; } ;
struct scmi_xfer {int /*<<< orphan*/  done; TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_info {struct scmi_xfers_info tx_minfo; struct scmi_desc* desc; struct device* dev; } ;
struct scmi_desc {int max_msg; int max_msg_size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSG_TOKEN_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scmi_xfer_info_init(struct scmi_info *sinfo)
{
	int i;
	struct scmi_xfer *xfer;
	struct device *dev = sinfo->dev;
	const struct scmi_desc *desc = sinfo->desc;
	struct scmi_xfers_info *info = &sinfo->tx_minfo;

	/* Pre-allocated messages, no more than what hdr.seq can support */
	if (WARN_ON(desc->max_msg >= MSG_TOKEN_MAX)) {
		dev_err(dev, "Maximum message of %d exceeds supported %ld\n",
			desc->max_msg, MSG_TOKEN_MAX);
		return -EINVAL;
	}

	info->xfer_block = devm_kcalloc(dev, desc->max_msg,
					sizeof(*info->xfer_block), GFP_KERNEL);
	if (!info->xfer_block)
		return -ENOMEM;

	info->xfer_alloc_table = devm_kcalloc(dev, BITS_TO_LONGS(desc->max_msg),
					      sizeof(long), GFP_KERNEL);
	if (!info->xfer_alloc_table)
		return -ENOMEM;

	/* Pre-initialize the buffer pointer to pre-allocated buffers */
	for (i = 0, xfer = info->xfer_block; i < desc->max_msg; i++, xfer++) {
		xfer->rx.buf = devm_kcalloc(dev, sizeof(u8), desc->max_msg_size,
					    GFP_KERNEL);
		if (!xfer->rx.buf)
			return -ENOMEM;

		xfer->tx.buf = xfer->rx.buf;
		init_completion(&xfer->done);
	}

	spin_lock_init(&info->xfer_lock);

	return 0;
}