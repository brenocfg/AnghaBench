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

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
#define  EV_CHN_COMMON 145 
#define  EV_CHN_VOICE 144 
#define  EV_SEQ_LOCAL 143 
#define  EV_SYSEX 142 
#define  EV_TIMING 141 
 int MIDI_NOTEOFF ; 
 int MIDI_NOTEON ; 
 int MIDI_PGM_CHANGE ; 
 int /*<<< orphan*/  MORE ; 
 int /*<<< orphan*/  QUEUEFULL ; 
#define  SEQ_AFTERTOUCH 140 
#define  SEQ_BALANCE 139 
#define  SEQ_CONTROLLER 138 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
#define  SEQ_ECHO 137 
#define  SEQ_EXTENDED 136 
#define  SEQ_MIDIPUTC 135 
#define  SEQ_NOTEOFF 134 
#define  SEQ_NOTEON 133 
#define  SEQ_PGMCHANGE 132 
#define  SEQ_PRIVATE 131 
#define  SEQ_SYNCTIMER 130 
#define  SEQ_VOLMODE 129 
#define  SEQ_WAIT 128 
 int TMR_WAIT_REL ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  ret ; 
 int /*<<< orphan*/  scp ; 
 int /*<<< orphan*/  seq_copytoinput (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
seq_convertold(u_char *event, u_char *out)
{
	int used;
	u_char dev, chn, note, vel;

	out[0] = out[1] = out[2] = out[3] = out[4] = out[5] = out[6] =
	    out[7] = 0;

	dev = 0;
	chn = event[1];
	note = event[2];
	vel = event[3];

	used = 0;

restart:
	/*
	 * TODO: Debug statement
	 */
	switch (event[0]) {
	case EV_TIMING:
	case EV_CHN_VOICE:
	case EV_CHN_COMMON:
	case EV_SYSEX:
	case EV_SEQ_LOCAL:
		out[0] = event[0];
		out[1] = event[1];
		out[2] = event[2];
		out[3] = event[3];
		out[4] = event[4];
		out[5] = event[5];
		out[6] = event[6];
		out[7] = event[7];
		used += 8;
		break;
	case SEQ_NOTEOFF:
		out[0] = EV_CHN_VOICE;
		out[1] = dev;
		out[2] = MIDI_NOTEOFF;
		out[3] = chn;
		out[4] = note;
		out[5] = 255;
		used += 4;
		break;

	case SEQ_NOTEON:
		out[0] = EV_CHN_VOICE;
		out[1] = dev;
		out[2] = MIDI_NOTEON;
		out[3] = chn;
		out[4] = note;
		out[5] = vel;
		used += 4;
		break;

		/*
		 * wait delay = (event[2] << 16) + (event[3] << 8) + event[4]
		 */

	case SEQ_PGMCHANGE:
		out[0] = EV_CHN_COMMON;
		out[1] = dev;
		out[2] = MIDI_PGM_CHANGE;
		out[3] = chn;
		out[4] = note;
		out[5] = vel;
		used += 4;
		break;
/*
		out[0] = EV_TIMING;
		out[1] = dev;
		out[2] = MIDI_PGM_CHANGE;
		out[3] = chn;
		out[4] = note;
		out[5] = vel;
		SEQ_DEBUG(4,printf("seq_playevent: synctimer\n"));
		break;
*/

	case SEQ_MIDIPUTC:
		SEQ_DEBUG(4,
		    printf("seq_playevent: put data 0x%02x, unit %d.\n",
		    event[1], event[2]));
		/*
		 * Pass through to the midi device.
		 * device = event[2]
		 * data = event[1]
		 */
		out[0] = SEQ_MIDIPUTC;
		out[1] = dev;
		out[2] = chn;
		used += 4;
		break;
#ifdef notyet
	case SEQ_ECHO:
		/*
		 * This isn't handled here yet because I don't know if I can
		 * just use four bytes events.  There might be consequences
		 * in the _read routing
		 */
		if (seq_copytoinput(scp, event, 4) == EAGAIN) {
			ret = QUEUEFULL;
			break;
		}
		ret = MORE;
		break;
#endif
	case SEQ_EXTENDED:
		switch (event[1]) {
		case SEQ_NOTEOFF:
		case SEQ_NOTEON:
		case SEQ_PGMCHANGE:
			event++;
			used = 4;
			goto restart;
			break;
		case SEQ_AFTERTOUCH:
			/*
			 * SYNTH_AFTERTOUCH(md, event[3], event[4])
			 */
		case SEQ_BALANCE:
			/*
			 * SYNTH_PANNING(md, event[3], (char)event[4])
			 */
		case SEQ_CONTROLLER:
			/*
			 * SYNTH_CONTROLLER(md, event[3], event[4], *(short *)&event[5])
			 */
		case SEQ_VOLMODE:
			/*
			 * SYNTH_VOLUMEMETHOD(md, event[3])
			 */
		default:
			SEQ_DEBUG(2,
			    printf("seq_convertold: SEQ_EXTENDED type %d"
			    "not handled\n", event[1]));
			break;
		}
		break;
	case SEQ_WAIT:
		out[0] = EV_TIMING;
		out[1] = TMR_WAIT_REL;
		out[4] = event[2];
		out[5] = event[3];
		out[6] = event[4];

		SEQ_DEBUG(5, printf("SEQ_WAIT %d",
		    event[2] + (event[3] << 8) + (event[4] << 24)));

		used += 4;
		break;

	case SEQ_ECHO:
	case SEQ_SYNCTIMER:
	case SEQ_PRIVATE:
	default:
		SEQ_DEBUG(2,
		  printf("seq_convertold: event type %d not handled %d %d %d\n",
		    event[0], event[1], event[2], event[3]));
		break;
	}
	return used;
}