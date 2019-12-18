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
struct seq_softc {int unit; scalar_t__ busy; int midi_number; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  mapper_cookie; int /*<<< orphan*/  mapper; scalar_t__* midis; } ;
struct cdev {struct seq_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTH_CLOSE (scalar_t__) ; 
 int /*<<< orphan*/  midimapper_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  seq_reset (struct seq_softc*) ; 
 int /*<<< orphan*/  seq_sync (struct seq_softc*) ; 
 int /*<<< orphan*/  timer_stop (struct seq_softc*) ; 

int
mseq_close(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	int i;
	struct seq_softc *scp = i_dev->si_drv1;
	int ret;

	if (scp == NULL)
		return ENXIO;

	SEQ_DEBUG(2, printf("seq_close: unit %d.\n", scp->unit));

	mtx_lock(&scp->seq_lock);

	ret = ENXIO;
	if (scp->busy == 0)
		goto err;

	seq_reset(scp);
	seq_sync(scp);

	for (i = 0; i < scp->midi_number; i++)
		if (scp->midis[i])
			SYNTH_CLOSE(scp->midis[i]);

	midimapper_close(scp->mapper, scp->mapper_cookie);

	timer_stop(scp);

	scp->busy = 0;
	ret = 0;

err:
	SEQ_DEBUG(3, printf("seq_close: closed ret = %d.\n", ret));
	mtx_unlock(&scp->seq_lock);
	return ret;
}