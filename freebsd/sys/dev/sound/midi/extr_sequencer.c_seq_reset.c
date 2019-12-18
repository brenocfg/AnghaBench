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
struct seq_softc {int unit; int midi_number; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/ * midis; int /*<<< orphan*/  out_q; int /*<<< orphan*/  in_q; int /*<<< orphan*/  reset_cv; int /*<<< orphan*/  out_cv; int /*<<< orphan*/  state_cv; scalar_t__ playing; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MIDIQ_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTH_BENDER (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SYNTH_CONTROLLER (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTH_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
seq_reset(struct seq_softc *scp)
{
	int chn, i;
	kobj_t m;

	mtx_assert(&scp->seq_lock, MA_OWNED);

	SEQ_DEBUG(5, printf("seq_reset: unit %d.\n", scp->unit));

	/*
	 * Stop reading and writing.
	 */

	/* scp->recording = 0; */
	scp->playing = 0;
	cv_broadcast(&scp->state_cv);
	cv_broadcast(&scp->out_cv);
	cv_broadcast(&scp->reset_cv);

	/*
	 * For now, don't reset the timers.
	 */
	MIDIQ_CLEAR(scp->in_q);
	MIDIQ_CLEAR(scp->out_q);

	for (i = 0; i < scp->midi_number; i++) {
		m = scp->midis[i];
		mtx_unlock(&scp->seq_lock);
		SYNTH_RESET(m);
		for (chn = 0; chn < 16; chn++) {
			SYNTH_CONTROLLER(m, chn, 123, 0);
			SYNTH_CONTROLLER(m, chn, 121, 0);
			SYNTH_BENDER(m, chn, 1 << 13);
		}
		mtx_lock(&scp->seq_lock);
	}
}