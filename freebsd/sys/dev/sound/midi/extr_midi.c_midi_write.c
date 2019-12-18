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
struct uio {int uio_resid; } ;
struct snd_midi {int flags; int wchan; int /*<<< orphan*/  lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  cookie; int /*<<< orphan*/  outq; int /*<<< orphan*/  busy; } ;
struct cdev {struct snd_midi* si_drv1; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int EINTR ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_ENQ (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int MIDI_WSIZE ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MPU_CALLBACK (struct snd_midi*,int /*<<< orphan*/ ,int) ; 
 int M_TX ; 
 int M_TXEN ; 
 int O_NONBLOCK ; 
 int PCATCH ; 
 int PDROP ; 
 int msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int uiomove (char*,int,struct uio*) ; 

int
midi_write(struct cdev *i_dev, struct uio *uio, int ioflag)
{
#define MIDI_WSIZE 32
	struct snd_midi *m = i_dev->si_drv1;
	int retval;
	int used;
	char buf[MIDI_WSIZE];


	MIDI_DEBUG(4, printf("midi_write\n"));
	retval = 0;
	if (m == NULL)
		goto err0;

	mtx_lock(&m->lock);
	mtx_lock(&m->qlock);

	if (!(m->flags & M_TX))
		goto err1;

	while (uio->uio_resid > 0) {
		while (MIDIQ_AVAIL(m->outq) == 0) {
			retval = EWOULDBLOCK;
			if (ioflag & O_NONBLOCK)
				goto err1;
			mtx_unlock(&m->lock);
			m->wchan = 1;
			MIDI_DEBUG(3, printf("midi_write msleep\n"));
			retval = msleep(&m->wchan, &m->qlock,
			    PCATCH | PDROP, "midi TX", 0);
			/*
			 * We slept, maybe things have changed since last
			 * dying check
			 */
			if (retval == EINTR)
				goto err0;
			if (m != i_dev->si_drv1)
				retval = ENXIO;
			if (retval)
				goto err0;
			mtx_lock(&m->lock);
			mtx_lock(&m->qlock);
			m->wchan = 0;
			if (!m->busy)
				goto err1;
		}

		/*
	         * We are certain than data can be placed on the queue
	         */

		used = MIN(MIDIQ_AVAIL(m->outq), uio->uio_resid);
		used = MIN(used, MIDI_WSIZE);
		MIDI_DEBUG(5, printf("midiout: resid %zd len %jd avail %jd\n",
		    uio->uio_resid, (intmax_t)MIDIQ_LEN(m->outq),
		    (intmax_t)MIDIQ_AVAIL(m->outq)));


		MIDI_DEBUG(5, printf("midi_write: uiomove cc=%d\n", used));
		retval = uiomove(buf, used, uio);
		if (retval)
			goto err1;
		MIDIQ_ENQ(m->outq, buf, used);
		/*
	         * Inform the bottom half that data can be written
	         */
		if (!(m->flags & M_TXEN)) {
			m->flags |= M_TXEN;
			MPU_CALLBACK(m, m->cookie, m->flags);
		}
	}
	/*
	 * If we Made it here then transfer is good
	 */
	retval = 0;
err1:	mtx_unlock(&m->qlock);
	mtx_unlock(&m->lock);
err0:	return retval;
}