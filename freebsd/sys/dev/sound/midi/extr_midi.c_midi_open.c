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
struct thread {int dummy; } ;
struct snd_midi {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  cookie; int /*<<< orphan*/  inq; scalar_t__ async; scalar_t__ wchan; scalar_t__ rchan; int /*<<< orphan*/  busy; int /*<<< orphan*/  outq; } ;
struct cdev {struct snd_midi* si_drv1; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  MIDIQ_CLEAR (int /*<<< orphan*/ ) ; 
 scalar_t__ MIDIQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_CALLBACK (struct snd_midi*,int /*<<< orphan*/ ,int) ; 
 int M_RX ; 
 int M_RXEN ; 
 int M_TX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
midi_open(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	struct snd_midi *m = i_dev->si_drv1;
	int retval;

	MIDI_DEBUG(1, printf("midiopen %p %s %s\n", td,
	    flags & FREAD ? "M_RX" : "", flags & FWRITE ? "M_TX" : ""));
	if (m == NULL)
		return ENXIO;

	mtx_lock(&m->lock);
	mtx_lock(&m->qlock);

	retval = 0;

	if (flags & FREAD) {
		if (MIDIQ_SIZE(m->inq) == 0)
			retval = ENXIO;
		else if (m->flags & M_RX)
			retval = EBUSY;
		if (retval)
			goto err;
	}
	if (flags & FWRITE) {
		if (MIDIQ_SIZE(m->outq) == 0)
			retval = ENXIO;
		else if (m->flags & M_TX)
			retval = EBUSY;
		if (retval)
			goto err;
	}
	m->busy++;

	m->rchan = 0;
	m->wchan = 0;
	m->async = 0;

	if (flags & FREAD) {
		m->flags |= M_RX | M_RXEN;
		/*
	         * Only clear the inq, the outq might still have data to drain
	         * from a previous session
	         */
		MIDIQ_CLEAR(m->inq);
	}

	if (flags & FWRITE)
		m->flags |= M_TX;

	MPU_CALLBACK(m, m->cookie, m->flags);

	MIDI_DEBUG(2, printf("midi_open: opened.\n"));

err:	mtx_unlock(&m->qlock);
	mtx_unlock(&m->lock);
	return retval;
}