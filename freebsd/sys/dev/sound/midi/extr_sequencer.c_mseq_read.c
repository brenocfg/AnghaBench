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
typedef  int /*<<< orphan*/  u_char ;
struct uio {int uio_resid; } ;
struct seq_softc {int unit; int fflags; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  in_q; int /*<<< orphan*/  in_cv; } ;
struct cdev {struct seq_softc* si_drv1; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int FREAD ; 
 int /*<<< orphan*/  MIDIQ_DEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int SEQ_RSIZE ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

int
mseq_read(struct cdev *i_dev, struct uio *uio, int ioflag)
{
	int retval, used;
	struct seq_softc *scp = i_dev->si_drv1;

#define SEQ_RSIZE 32
	u_char buf[SEQ_RSIZE];

	if (scp == NULL)
		return ENXIO;

	SEQ_DEBUG(7, printf("mseq_read: unit %d, resid %zd.\n",
	    scp->unit, uio->uio_resid));

	mtx_lock(&scp->seq_lock);
	if ((scp->fflags & FREAD) == 0) {
		SEQ_DEBUG(2, printf("mseq_read: unit %d is not for reading.\n",
		    scp->unit));
		retval = EIO;
		goto err1;
	}
	/*
	 * Begin recording.
	 */
	/*
	 * if ((scp->flags & SEQ_F_READING) == 0)
	 */
	/*
	 * TODO, start recording if not alread
	 */

	/*
	 * I think the semantics are to return as soon
	 * as possible.
	 * Second thought, it doens't seem like midimoutain
	 * expects that at all.
	 * TODO: Look up in some sort of spec
	 */

	while (uio->uio_resid > 0) {
		while (MIDIQ_EMPTY(scp->in_q)) {
			retval = EWOULDBLOCK;
			/*
			 * I wish I knew which one to care about
			 */

			if (scp->fflags & O_NONBLOCK)
				goto err1;
			if (ioflag & O_NONBLOCK)
				goto err1;

			retval = cv_wait_sig(&scp->in_cv, &scp->seq_lock);
			if (retval != 0)
				goto err1;
		}

		used = MIN(MIDIQ_LEN(scp->in_q), uio->uio_resid);
		used = MIN(used, SEQ_RSIZE);

		SEQ_DEBUG(8, printf("midiread: uiomove cc=%d\n", used));
		MIDIQ_DEQ(scp->in_q, buf, used);
		mtx_unlock(&scp->seq_lock);
		retval = uiomove(buf, used, uio);
		mtx_lock(&scp->seq_lock);
		if (retval)
			goto err1;
	}

	retval = 0;
err1:
	mtx_unlock(&scp->seq_lock);
	SEQ_DEBUG(6, printf("mseq_read: ret %d, resid %zd.\n",
	    retval, uio->uio_resid));

	return retval;
}