#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct uio {int dummy; } ;
struct tcode_info {int /*<<< orphan*/  hdr_len; } ;
struct TYPE_9__ {size_t tcode; } ;
struct TYPE_10__ {TYPE_1__ hdr; int /*<<< orphan*/  ld; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  pay_len; struct fw_pkt* payload; struct fw_pkt hdr; } ;
struct fw_xfer {TYPE_6__* fc; TYPE_3__ recv; scalar_t__ sc; } ;
struct fw_drv1 {int /*<<< orphan*/  rq; TYPE_6__* fc; } ;
struct fw_bind {int /*<<< orphan*/  xferlist; } ;
struct TYPE_13__ {struct tcode_info* tcode; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* irx_post ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FWPRI ; 
 int /*<<< orphan*/  FW_GLOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  FW_GMTX (TYPE_6__*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fw_xfer* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* fc ; 
 int /*<<< orphan*/  fw_xfer_unload (struct fw_xfer*) ; 
 int /*<<< orphan*/  link ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int uiomove (struct fw_pkt*,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
fw_read_async(struct fw_drv1 *d, struct uio *uio, int ioflag)
{
	int err = 0, s;
	struct fw_xfer *xfer;
	struct fw_bind *fwb;
	struct fw_pkt *fp;
	struct tcode_info *tinfo;

	FW_GLOCK(d->fc);
	while ((xfer = STAILQ_FIRST(&d->rq)) == NULL && err == 0)
		err = msleep(&d->rq, FW_GMTX(d->fc), FWPRI, "fwra", 0);

	if (err != 0) {
		FW_GUNLOCK(d->fc);
		return (err);
	}

	s = splfw();
	STAILQ_REMOVE_HEAD(&d->rq, link);
	FW_GUNLOCK(xfer->fc);
	splx(s);
	fp = &xfer->recv.hdr;
#if 0 /* for GASP ?? */
	if (fc->irx_post != NULL)
		fc->irx_post(fc, fp->mode.ld);
#endif
	tinfo = &xfer->fc->tcode[fp->mode.hdr.tcode];
	err = uiomove(fp, tinfo->hdr_len, uio);
	if (err)
		goto out;
	err = uiomove(xfer->recv.payload, xfer->recv.pay_len, uio);

out:
	/* recycle this xfer */
	fwb = (struct fw_bind *)xfer->sc;
	fw_xfer_unload(xfer);
	xfer->recv.pay_len = PAGE_SIZE;
	FW_GLOCK(xfer->fc);
	STAILQ_INSERT_TAIL(&fwb->xferlist, xfer, link);
	FW_GUNLOCK(xfer->fc);
	return (err);
}