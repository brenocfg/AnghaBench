#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_midi {struct snd_midi* synth; int /*<<< orphan*/  lock; int /*<<< orphan*/  qlock; int /*<<< orphan*/  outq; int /*<<< orphan*/  inq; int /*<<< orphan*/  cookie; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct snd_midi* MIDIQ_BUF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_UNINIT (struct snd_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MIDI ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct snd_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct snd_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  midi_devs ; 
 int /*<<< orphan*/  midistat_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
midi_destroy(struct snd_midi *m, int midiuninit)
{
	sx_assert(&midistat_lock, SA_XLOCKED);
	mtx_assert(&m->lock, MA_OWNED);

	MIDI_DEBUG(3, printf("midi_destroy\n"));
	m->dev->si_drv1 = NULL;
	mtx_unlock(&m->lock);	/* XXX */
	destroy_dev(m->dev);
	TAILQ_REMOVE(&midi_devs, m, link);
	if (midiuninit)
		MPU_UNINIT(m, m->cookie);
	free(MIDIQ_BUF(m->inq), M_MIDI);
	free(MIDIQ_BUF(m->outq), M_MIDI);
	mtx_destroy(&m->qlock);
	mtx_destroy(&m->lock);
	free(m->synth, M_MIDI);
	free(m, M_MIDI);
	return 0;
}