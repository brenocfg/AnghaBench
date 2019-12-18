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
struct snd_midi {int flags; scalar_t__ hiwat; int /*<<< orphan*/  qlock; scalar_t__ async; int /*<<< orphan*/  wsel; scalar_t__ wchan; int /*<<< orphan*/  outq; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  MIDI_TYPE ;

/* Variables and functions */
 scalar_t__ MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_DEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MIDIQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_CALLBACKP (struct snd_midi*,int /*<<< orphan*/ ,int) ; 
 int M_TXEN ; 
 int /*<<< orphan*/  PROC_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PROC_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kern_psignal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
midi_out(struct snd_midi *m, MIDI_TYPE *buf, int size)
{
	int used;

/*
 * XXX: locking flub
 */
	if (!(m->flags & M_TXEN))
		return 0;

	MIDI_DEBUG(2, printf("midi_out: %p\n", m));
	mtx_lock(&m->qlock);
	used = MIN(size, MIDIQ_LEN(m->outq));
	MIDI_DEBUG(3, printf("midi_out: used %d\n", used));
	if (used)
		MIDIQ_DEQ(m->outq, buf, used);
	if (MIDIQ_EMPTY(m->outq)) {
		m->flags &= ~M_TXEN;
		MPU_CALLBACKP(m, m->cookie, m->flags);
	}
	if (used && MIDIQ_AVAIL(m->outq) > m->hiwat) {
		if (m->wchan) {
			wakeup(&m->wchan);
			m->wchan = 0;
		}
		selwakeup(&m->wsel);
		if (m->async) {
			PROC_LOCK(m->async);
			kern_psignal(m->async, SIGIO);
			PROC_UNLOCK(m->async);
		}
	}
	mtx_unlock(&m->qlock);
	return used;
}