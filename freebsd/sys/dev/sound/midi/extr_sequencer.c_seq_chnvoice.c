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
typedef  int u_char ;
struct seq_softc {int unit; int /*<<< orphan*/  seq_lock; int /*<<< orphan*/  music; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
#define  MIDI_KEY_PRESSURE 130 
#define  MIDI_NOTEOFF 129 
#define  MIDI_NOTEON 128 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNTH_AFTERTOUCH (int /*<<< orphan*/ ,int,int) ; 
 int SYNTH_ALLOC (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SYNTH_KILLNOTE (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SYNTH_STARTNOTE (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cmdtab_seqcv ; 
 char* midi_cmdname (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
seq_chnvoice(struct seq_softc *scp, kobj_t md, u_char *event)
{
	int ret, voice;
	u_char cmd, chn, note, parm;

	ret = 0;
	cmd = event[2];
	chn = event[3];
	note = event[4];
	parm = event[5];

	mtx_assert(&scp->seq_lock, MA_OWNED);

	SEQ_DEBUG(5, printf("seq_chnvoice: unit %d, dev %d, cmd %s,"
	    " chn %d, note %d, parm %d.\n", scp->unit, event[1],
	    midi_cmdname(cmd, cmdtab_seqcv), chn, note, parm));

	voice = SYNTH_ALLOC(md, chn, note);

	mtx_unlock(&scp->seq_lock);

	switch (cmd) {
	case MIDI_NOTEON:
		if (note < 128 || note == 255) {
#if 0
			if (scp->music && chn == 9) {
				/*
				 * This channel is a percussion. The note
				 * number is the patch number.
				 */
				/*
				mtx_unlock(&scp->seq_lock);
				if (SYNTH_SETINSTR(md, voice, 128 + note)
				    == EAGAIN) {
					mtx_lock(&scp->seq_lock);
					return (QUEUEFULL);
				}
				mtx_lock(&scp->seq_lock);
				*/
				note = 60;	/* Middle C. */
			}
#endif
			if (scp->music) {
				/*
				mtx_unlock(&scp->seq_lock);
				if (SYNTH_SETUPVOICE(md, voice, chn)
				    == EAGAIN) {
					mtx_lock(&scp->seq_lock);
					return (QUEUEFULL);
				}
				mtx_lock(&scp->seq_lock);
				*/
			}
			SYNTH_STARTNOTE(md, voice, note, parm);
		}
		break;
	case MIDI_NOTEOFF:
		SYNTH_KILLNOTE(md, voice, note, parm);
		break;
	case MIDI_KEY_PRESSURE:
		SYNTH_AFTERTOUCH(md, voice, parm);
		break;
	default:
		ret = 1;
		SEQ_DEBUG(2, printf("seq_chnvoice event type %d not handled\n",
		    event[1]));
		break;
	}

	mtx_lock(&scp->seq_lock);
	return ret;
}