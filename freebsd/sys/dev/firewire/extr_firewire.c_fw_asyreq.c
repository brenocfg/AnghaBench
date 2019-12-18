#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcode_info {int flag; int hdr_len; } ;
struct fw_xferq {scalar_t__ queued; scalar_t__ maxq; int /*<<< orphan*/ * start; } ;
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {int len; } ;
struct TYPE_8__ {int dest_hi; int dest_lo; } ;
struct TYPE_7__ {int tcode; } ;
struct TYPE_11__ {TYPE_4__ rresb; TYPE_3__ stream; TYPE_2__ rreqq; TYPE_1__ common; } ;
struct fw_pkt {TYPE_5__ mode; } ;
struct TYPE_12__ {int pay_len; struct fw_pkt hdr; } ;
struct fw_xfer {int resp; int tl; struct fw_xferq* q; struct firewire_comm* fc; TYPE_6__ send; int /*<<< orphan*/  flag; int /*<<< orphan*/ * hand; } ;
struct firewire_comm {scalar_t__ status; int /*<<< orphan*/  bdev; int /*<<< orphan*/  maxrec; struct fw_xferq* ats; struct fw_xferq* atq; struct tcode_info* tcode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ FWBUSEXPLORE ; 
 int FWTCODE_RREQQ ; 
 int FWTI_BLOCK_ASY ; 
 int FWTI_BLOCK_STR ; 
 int FWTI_REQ ; 
 int FWTI_TLABEL ; 
 int /*<<< orphan*/  FWXF_BUSY ; 
 int MAXREC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fw_asystart (struct fw_xfer*) ; 
 scalar_t__ fw_get_tlabel (struct firewire_comm*,struct fw_xfer*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** tcode_str ; 

int
fw_asyreq(struct firewire_comm *fc, int sub, struct fw_xfer *xfer)
{
	int err = 0;
	struct fw_xferq *xferq;
	int len;
	struct fw_pkt *fp;
	int tcode;
	struct tcode_info *info;

	if (xfer == NULL)
		return EINVAL;
	if (xfer->hand == NULL) {
		printf("hand == NULL\n");
		return EINVAL;
	}
	fp = &xfer->send.hdr;

	tcode = fp->mode.common.tcode & 0xf;
	info = &fc->tcode[tcode];
	if (info->flag == 0) {
		printf("invalid tcode=%x\n", tcode);
		return EINVAL;
	}

	/* XXX allow bus explore packets only after bus rest */
	if ((fc->status < FWBUSEXPLORE) &&
	    ((tcode != FWTCODE_RREQQ) || (fp->mode.rreqq.dest_hi != 0xffff) ||
	    (fp->mode.rreqq.dest_lo  < 0xf0000000) ||
	    (fp->mode.rreqq.dest_lo >= 0xf0001000))) {
		xfer->resp = EAGAIN;
		xfer->flag = FWXF_BUSY;
		return (EAGAIN);
	}

	if (info->flag & FWTI_REQ)
		xferq = fc->atq;
	else
		xferq = fc->ats;
	len = info->hdr_len;
	if (xfer->send.pay_len > MAXREC(fc->maxrec)) {
		printf("send.pay_len > maxrec\n");
		return EINVAL;
	}
	if (info->flag & FWTI_BLOCK_STR)
		len = fp->mode.stream.len;
	else if (info->flag & FWTI_BLOCK_ASY)
		len = fp->mode.rresb.len;
	else
		len = 0;
	if (len != xfer->send.pay_len) {
		printf("len(%d) != send.pay_len(%d) %s(%x)\n",
		    len, xfer->send.pay_len, tcode_str[tcode], tcode);
		return EINVAL;
	}

	if (xferq->start == NULL) {
		printf("xferq->start == NULL\n");
		return EINVAL;
	}
	if (!(xferq->queued < xferq->maxq)) {
		device_printf(fc->bdev, "Discard a packet (queued=%d)\n",
			xferq->queued);
		return EAGAIN;
	}

	xfer->tl = -1;
	if (info->flag & FWTI_TLABEL) {
		if (fw_get_tlabel(fc, xfer) < 0)
			return EAGAIN;
	}

	xfer->resp = 0;
	xfer->fc = fc;
	xfer->q = xferq;

	fw_asystart(xfer);
	return err;
}