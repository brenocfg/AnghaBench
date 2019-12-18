#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uio {int uio_resid; } ;
struct fw_xferq {scalar_t__ queued; scalar_t__ bnpacket; int /*<<< orphan*/  dmach; TYPE_3__* stproc; int /*<<< orphan*/  stvalid; int /*<<< orphan*/ * buf; int /*<<< orphan*/  stfree; } ;
struct TYPE_5__ {int len; scalar_t__ payload; } ;
struct TYPE_6__ {TYPE_1__ stream; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct fw_isohdr {int dummy; } ;
struct fw_drv1 {struct fw_xferq* it; struct firewire_comm* fc; } ;
struct firewire_comm {int (* itx_enable ) (struct firewire_comm*,int /*<<< orphan*/ ) ;} ;
struct cdev {struct fw_drv1* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {scalar_t__ poffset; } ;

/* Variables and functions */
 scalar_t__ DEV_FWMEM (struct cdev*) ; 
 int EIO ; 
 int /*<<< orphan*/  FWPRI ; 
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GMTX (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 TYPE_3__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fw_write_async (struct fw_drv1*,struct uio*,int) ; 
 scalar_t__ fwdma_v_addr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  link ; 
 int msleep (struct fw_xferq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int physio (struct cdev*,struct uio*,int) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 
 int stub1 (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 int stub2 (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
fw_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	int err = 0;
	int s, slept = 0;
	struct fw_drv1 *d;
	struct fw_pkt *fp;
	struct firewire_comm *fc;
	struct fw_xferq *it;

	if (DEV_FWMEM(dev))
		return (physio(dev, uio, ioflag));

	d = dev->si_drv1;
	fc = d->fc;
	it = d->it;

	if (it == NULL)
		return (fw_write_async(d, uio, ioflag));

	if (it->buf == NULL)
		return (EIO);

	FW_GLOCK(fc);
isoloop:
	if (it->stproc == NULL) {
		it->stproc = STAILQ_FIRST(&it->stfree);
		if (it->stproc != NULL) {
			s = splfw();
			STAILQ_REMOVE_HEAD(&it->stfree, link);
			splx(s);
			it->queued = 0;
		} else if (slept == 0) {
			slept = 1;
#if 0	/* XXX to avoid lock recursion */
			err = fc->itx_enable(fc, it->dmach);
			if (err)
				goto out;
#endif
			err = msleep(it, FW_GMTX(fc), FWPRI, "fw_write", hz);
			if (err)
				goto out;
			goto isoloop;
		} else {
			err = EIO;
			goto out;
		}
	}
	FW_GUNLOCK(fc);
	fp = (struct fw_pkt *)fwdma_v_addr(it->buf,
			it->stproc->poffset + it->queued);
	err = uiomove((caddr_t)fp, sizeof(struct fw_isohdr), uio);
	err = uiomove((caddr_t)fp->mode.stream.payload,
				fp->mode.stream.len, uio);
	it->queued++;
	if (it->queued >= it->bnpacket) {
		s = splfw();
		STAILQ_INSERT_TAIL(&it->stvalid, it->stproc, link);
		splx(s);
		it->stproc = NULL;
		err = fc->itx_enable(fc, it->dmach);
	}
	if (uio->uio_resid >= sizeof(struct fw_isohdr)) {
		slept = 0;
		FW_GLOCK(fc);
		goto isoloop;
	}
	return err;

out:
	FW_GUNLOCK(fc);
	return err;
}