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
struct snd_midi {int flags; int rchan; int /*<<< orphan*/  lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  inq; int /*<<< orphan*/  busy; } ;
struct cdev {struct snd_midi* si_drv1; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MIDIQ_DEQ (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int MIDI_RSIZE ; 
 int MIN (int,int) ; 
 int M_RX ; 
 int O_NONBLOCK ; 
 int PCATCH ; 
 int PDROP ; 
 int msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int uiomove (char*,int,struct uio*) ; 

int
midi_read(struct cdev *i_dev, struct uio *uio, int ioflag)
{
#define MIDI_RSIZE 32
	struct snd_midi *m = i_dev->si_drv1;
	int retval;
	int used;
	char buf[MIDI_RSIZE];

	MIDI_DEBUG(5, printf("midiread: count=%lu\n",
	    (unsigned long)uio->uio_resid));

	retval = EIO;

	if (m == NULL)
		goto err0;

	mtx_lock(&m->lock);
	mtx_lock(&m->qlock);

	if (!(m->flags & M_RX))
		goto err1;

	while (uio->uio_resid > 0) {
		while (MIDIQ_EMPTY(m->inq)) {
			retval = EWOULDBLOCK;
			if (ioflag & O_NONBLOCK)
				goto err1;
			mtx_unlock(&m->lock);
			m->rchan = 1;
			retval = msleep(&m->rchan, &m->qlock,
			    PCATCH | PDROP, "midi RX", 0);
			/*
			 * We slept, maybe things have changed since last
			 * dying check
			 */
			if (retval == EINTR)
				goto err0;
			if (m != i_dev->si_drv1)
				retval = ENXIO;
			/* if (retval && retval != ERESTART) */
			if (retval)
				goto err0;
			mtx_lock(&m->lock);
			mtx_lock(&m->qlock);
			m->rchan = 0;
			if (!m->busy)
				goto err1;
		}
		MIDI_DEBUG(6, printf("midi_read start\n"));
		/*
	         * At this point, it is certain that m->inq has data
	         */

		used = MIN(MIDIQ_LEN(m->inq), uio->uio_resid);
		used = MIN(used, MIDI_RSIZE);

		MIDI_DEBUG(6, printf("midiread: uiomove cc=%d\n", used));
		MIDIQ_DEQ(m->inq, buf, used);
		retval = uiomove(buf, used, uio);
		if (retval)
			goto err1;
	}

	/*
	 * If we Made it here then transfer is good
	 */
	retval = 0;
err1:	mtx_unlock(&m->qlock);
	mtx_unlock(&m->lock);
err0:	MIDI_DEBUG(4, printf("midi_read: ret %d\n", retval));
	return retval;
}