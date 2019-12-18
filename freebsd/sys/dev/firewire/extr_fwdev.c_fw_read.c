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
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {scalar_t__ uio_resid; } ;
struct fw_xferq {scalar_t__ queued; scalar_t__ bnpacket; scalar_t__ psize; TYPE_3__* stproc; int /*<<< orphan*/  dmach; int /*<<< orphan*/  stfree; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flag; int /*<<< orphan*/  stvalid; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_6__ {TYPE_1__ stream; int /*<<< orphan*/  ld; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct fw_drv1 {struct fw_xferq* ir; struct firewire_comm* fc; } ;
struct firewire_comm {int /*<<< orphan*/  (* irx_enable ) (struct firewire_comm*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* irx_post ) (struct firewire_comm*,int /*<<< orphan*/ ) ;} ;
struct cdev {struct fw_drv1* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {scalar_t__ poffset; } ;

/* Variables and functions */
 scalar_t__ DEV_FWMEM (struct cdev*) ; 
 int EIO ; 
 int /*<<< orphan*/  FWPRI ; 
 int /*<<< orphan*/  FWXFERQ_WAKEUP ; 
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GMTX (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 TYPE_3__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fw_read_async (struct fw_drv1*,struct uio*,int) ; 
 scalar_t__ fwdma_v_addr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  link ; 
 int msleep (struct fw_xferq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int physio (struct cdev*,struct uio*,int) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  stub1 (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ ,scalar_t__,struct uio*) ; 

__attribute__((used)) static int
fw_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct fw_drv1 *d;
	struct fw_xferq *ir;
	struct firewire_comm *fc;
	int err = 0, s, slept = 0;
	struct fw_pkt *fp;

	if (DEV_FWMEM(dev))
		return (physio(dev, uio, ioflag));

	d = dev->si_drv1;
	fc = d->fc;
	ir = d->ir;

	if (ir == NULL)
		return (fw_read_async(d, uio, ioflag));

	if (ir->buf == NULL)
		return (EIO);

	FW_GLOCK(fc);
readloop:
	if (ir->stproc == NULL) {
		/* iso bulkxfer */
		ir->stproc = STAILQ_FIRST(&ir->stvalid);
		if (ir->stproc != NULL) {
			s = splfw();
			STAILQ_REMOVE_HEAD(&ir->stvalid, link);
			splx(s);
			ir->queued = 0;
		}
	}
	if (ir->stproc == NULL) {
		/* no data available */
		if (slept == 0) {
			slept = 1;
			ir->flag |= FWXFERQ_WAKEUP;
			err = msleep(ir, FW_GMTX(fc), FWPRI, "fw_read", hz);
			ir->flag &= ~FWXFERQ_WAKEUP;
			if (err == 0)
				goto readloop;
		} else if (slept == 1)
			err = EIO;
		FW_GUNLOCK(fc);
		return err;
	} else if (ir->stproc != NULL) {
		/* iso bulkxfer */
		FW_GUNLOCK(fc);
		fp = (struct fw_pkt *)fwdma_v_addr(ir->buf,
		    ir->stproc->poffset + ir->queued);
		if (fc->irx_post != NULL)
			fc->irx_post(fc, fp->mode.ld);
		if (fp->mode.stream.len == 0) {
			err = EIO;
			return err;
		}
		err = uiomove((caddr_t)fp,
			fp->mode.stream.len + sizeof(uint32_t), uio);
		ir->queued++;
		if (ir->queued >= ir->bnpacket) {
			s = splfw();
			STAILQ_INSERT_TAIL(&ir->stfree, ir->stproc, link);
			splx(s);
			fc->irx_enable(fc, ir->dmach);
			ir->stproc = NULL;
		}
		if (uio->uio_resid >= ir->psize) {
			slept = -1;
			FW_GLOCK(fc);
			goto readloop;
		}
	}
	return err;
}