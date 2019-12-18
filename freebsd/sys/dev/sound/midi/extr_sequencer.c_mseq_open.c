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
struct seq_softc {int unit; int busy; int fflags; int music; size_t midi_number; int maxunits; int out_water; int /*<<< orphan*/ ** midis; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  out_q; int /*<<< orphan*/ * midi_flags; int /*<<< orphan*/  mapper_cookie; int /*<<< orphan*/  mapper; } ;
struct cdev {struct seq_softc* si_drv1; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 scalar_t__ MIDIDEV (struct cdev*) ; 
 int MIDIQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SND_DEV_MUSIC ; 
 scalar_t__ SYNTH_OPEN (int /*<<< orphan*/ *,struct seq_softc*,int) ; 
 int /*<<< orphan*/  SYNTH_QUERY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * midimapper_fetch_synth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int midimapper_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  timer_setvals (struct seq_softc*,int,int) ; 
 int /*<<< orphan*/  timer_start (struct seq_softc*) ; 
 int /*<<< orphan*/  timer_stop (struct seq_softc*) ; 

int
mseq_open(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	struct seq_softc *scp = i_dev->si_drv1;
	int i;

	if (scp == NULL)
		return ENXIO;

	SEQ_DEBUG(3, printf("seq_open: scp %p unit %d, flags 0x%x.\n",
	    scp, scp->unit, flags));

	/*
	 * Mark this device busy.
	 */

	mtx_lock(&scp->seq_lock);
	if (scp->busy) {
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(2, printf("seq_open: unit %d is busy.\n", scp->unit));
		return EBUSY;
	}
	scp->fflags = flags;
	/*
	if ((scp->fflags & O_NONBLOCK) != 0)
		scp->flags |= SEQ_F_NBIO;
		*/
	scp->music = MIDIDEV(i_dev) == SND_DEV_MUSIC;

	/*
	 * Enumerate the available midi devices
	 */
	scp->midi_number = 0;
	scp->maxunits = midimapper_open(scp->mapper, &scp->mapper_cookie);

	if (scp->maxunits == 0)
		SEQ_DEBUG(2, printf("seq_open: no midi devices\n"));

	for (i = 0; i < scp->maxunits; i++) {
		scp->midis[scp->midi_number] =
		    midimapper_fetch_synth(scp->mapper, scp->mapper_cookie, i);
		if (scp->midis[scp->midi_number]) {
			if (SYNTH_OPEN(scp->midis[scp->midi_number], scp,
				scp->fflags) != 0)
				scp->midis[scp->midi_number] = NULL;
			else {
				scp->midi_flags[scp->midi_number] =
				    SYNTH_QUERY(scp->midis[scp->midi_number]);
				scp->midi_number++;
			}
		}
	}

	timer_setvals(scp, 60, 100);

	timer_start(scp);
	timer_stop(scp);
	/*
	 * actually, if we're in rdonly mode, we should start the timer
	 */
	/*
	 * TODO: Handle recording now
	 */

	scp->out_water = MIDIQ_SIZE(scp->out_q) / 2;

	scp->busy = 1;
	mtx_unlock(&scp->seq_lock);

	SEQ_DEBUG(2, printf("seq_open: opened, mode %s.\n",
	    scp->music ? "music" : "sequencer"));
	SEQ_DEBUG(2,
	    printf("Sequencer %d %p opened maxunits %d midi_number %d:\n",
		scp->unit, scp, scp->maxunits, scp->midi_number));
	for (i = 0; i < scp->midi_number; i++)
		SEQ_DEBUG(3, printf("  midi %d %p\n", i, scp->midis[i]));

	return 0;
}