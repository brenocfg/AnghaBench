#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {int uio_resid; } ;
struct tcode_info {int hdr_len; } ;
struct TYPE_9__ {int pay_len; int spd; int /*<<< orphan*/ * payload; int /*<<< orphan*/  hdr; } ;
struct fw_xfer {int resp; int flag; TYPE_4__* fc; TYPE_3__ send; int /*<<< orphan*/  hand; int /*<<< orphan*/ * sc; } ;
struct TYPE_7__ {size_t tcode; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct fw_drv1 {int /*<<< orphan*/  rq; TYPE_4__* fc; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_10__ {struct tcode_info* tcode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FWXF_RCVD ; 
 int /*<<< orphan*/  FW_GLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  M_FWXFER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct fw_pkt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct fw_pkt*,int) ; 
 int fw_asyreq (TYPE_4__*,int,struct fw_xfer*) ; 
 struct fw_xfer* fw_xfer_alloc_buf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_xfer_free (struct fw_xfer*) ; 
 int fw_xferwait (struct fw_xfer*) ; 
 int /*<<< orphan*/  fw_xferwake ; 
 int /*<<< orphan*/  link ; 
 int uiomove (scalar_t__,int,struct uio*) ; 

__attribute__((used)) static int
fw_write_async(struct fw_drv1 *d, struct uio *uio, int ioflag)
{
	struct fw_xfer *xfer;
	struct fw_pkt pkt;
	struct tcode_info *tinfo;
	int err;

	bzero(&pkt, sizeof(struct fw_pkt));
	if ((err = uiomove((caddr_t)&pkt, sizeof(uint32_t), uio)))
		return (err);
	tinfo = &d->fc->tcode[pkt.mode.hdr.tcode];
	if ((err = uiomove((caddr_t)&pkt + sizeof(uint32_t),
	    tinfo->hdr_len - sizeof(uint32_t), uio)))
		return (err);

	if ((xfer = fw_xfer_alloc_buf(M_FWXFER, uio->uio_resid,
	    PAGE_SIZE/*XXX*/)) == NULL)
		return (ENOMEM);

	bcopy(&pkt, &xfer->send.hdr, sizeof(struct fw_pkt));
	xfer->send.pay_len = uio->uio_resid;
	if (uio->uio_resid > 0) {
		if ((err = uiomove((caddr_t)&xfer->send.payload[0],
		    uio->uio_resid, uio)))
			goto out;
	}

	xfer->fc = d->fc;
	xfer->sc = NULL;
	xfer->hand = fw_xferwake;
	xfer->send.spd = 2 /* XXX */;

	if ((err = fw_asyreq(xfer->fc, -1, xfer)))
		goto out;

	if ((err = fw_xferwait(xfer)))
		goto out;

	if (xfer->resp != 0) {
		err = xfer->resp;
		goto out;
	}

	if (xfer->flag & FWXF_RCVD) {
		FW_GLOCK(xfer->fc);
		STAILQ_INSERT_TAIL(&d->rq, xfer, link);
		FW_GUNLOCK(xfer->fc);
		return (0);
	}

out:
	fw_xfer_free(xfer);
	return (err);
}