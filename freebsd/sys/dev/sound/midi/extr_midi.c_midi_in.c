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
struct snd_midi {int flags; int inq_state; int inq_left; scalar_t__ inq_status; int /*<<< orphan*/  qlock; scalar_t__ async; int /*<<< orphan*/  rsel; scalar_t__ rchan; int /*<<< orphan*/  inq; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ MIDI_TYPE ;

/* Variables and functions */
 int MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_ENQ (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  MIDIQ_FULL (int /*<<< orphan*/ ) ; 
 scalar_t__ MIDIQ_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ MIDI_ACK ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
#define  MIDI_IN_DATA 130 
#define  MIDI_IN_START 129 
#define  MIDI_IN_SYSEX 128 
 int /*<<< orphan*/  MIDI_IS_COMMON (scalar_t__) ; 
 int /*<<< orphan*/  MIDI_IS_STATUS (scalar_t__) ; 
 int MIDI_LENGTH (scalar_t__) ; 
 scalar_t__ MIDI_SYSEX_END ; 
 int M_RX ; 
 int /*<<< orphan*/  PROC_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PROC_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  SIGIO ; 
 scalar_t__ data ; 
 int enq ; 
 int i ; 
 int /*<<< orphan*/  kern_psignal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int sig ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
midi_in(struct snd_midi *m, MIDI_TYPE *buf, int size)
{
	/* int             i, sig, enq; */
	int used;

	/* MIDI_TYPE       data; */
	MIDI_DEBUG(5, printf("midi_in: m=%p size=%d\n", m, size));

/*
 * XXX: locking flub
 */
	if (!(m->flags & M_RX))
		return size;

	used = 0;

	mtx_lock(&m->qlock);
#if 0
	/*
	 * Don't bother queuing if not in read mode.  Discard everything and
	 * return size so the caller doesn't freak out.
	 */

	if (!(m->flags & M_RX))
		return size;

	for (i = sig = 0; i < size; i++) {

		data = buf[i];
		enq = 0;
		if (data == MIDI_ACK)
			continue;

		switch (m->inq_state) {
		case MIDI_IN_START:
			if (MIDI_IS_STATUS(data)) {
				switch (data) {
				case 0xf0:	/* Sysex */
					m->inq_state = MIDI_IN_SYSEX;
					break;
				case 0xf1:	/* MTC quarter frame */
				case 0xf3:	/* Song select */
					m->inq_state = MIDI_IN_DATA;
					enq = 1;
					m->inq_left = 1;
					break;
				case 0xf2:	/* Song position pointer */
					m->inq_state = MIDI_IN_DATA;
					enq = 1;
					m->inq_left = 2;
					break;
				default:
					if (MIDI_IS_COMMON(data)) {
						enq = 1;
						sig = 1;
					} else {
						m->inq_state = MIDI_IN_DATA;
						enq = 1;
						m->inq_status = data;
						m->inq_left = MIDI_LENGTH(data);
					}
					break;
				}
			} else if (MIDI_IS_STATUS(m->inq_status)) {
				m->inq_state = MIDI_IN_DATA;
				if (!MIDIQ_FULL(m->inq)) {
					used++;
					MIDIQ_ENQ(m->inq, &m->inq_status, 1);
				}
				enq = 1;
				m->inq_left = MIDI_LENGTH(m->inq_status) - 1;
			}
			break;
			/*
			 * End of case MIDI_IN_START:
			 */

		case MIDI_IN_DATA:
			enq = 1;
			if (--m->inq_left <= 0)
				sig = 1;/* deliver data */
			break;
		case MIDI_IN_SYSEX:
			if (data == MIDI_SYSEX_END)
				m->inq_state = MIDI_IN_START;
			break;
		}

		if (enq)
			if (!MIDIQ_FULL(m->inq)) {
				MIDIQ_ENQ(m->inq, &data, 1);
				used++;
			}
		/*
	         * End of the state machines main "for loop"
	         */
	}
	if (sig) {
#endif
		MIDI_DEBUG(6, printf("midi_in: len %jd avail %jd\n",
		    (intmax_t)MIDIQ_LEN(m->inq),
		    (intmax_t)MIDIQ_AVAIL(m->inq)));
		if (MIDIQ_AVAIL(m->inq) > size) {
			used = size;
			MIDIQ_ENQ(m->inq, buf, size);
		} else {
			MIDI_DEBUG(4, printf("midi_in: Discarding data qu\n"));
			mtx_unlock(&m->qlock);
			return 0;
		}
		if (m->rchan) {
			wakeup(&m->rchan);
			m->rchan = 0;
		}
		selwakeup(&m->rsel);
		if (m->async) {
			PROC_LOCK(m->async);
			kern_psignal(m->async, SIGIO);
			PROC_UNLOCK(m->async);
		}
#if 0
	}
#endif
	mtx_unlock(&m->qlock);
	return used;
}