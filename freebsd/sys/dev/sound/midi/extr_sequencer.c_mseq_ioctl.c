#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_char ;
struct thread {int dummy; } ;
struct synth_info {int device; float* name; int dev_type; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  synth_type; } ;
struct TYPE_4__ {int fl; } ;
struct TYPE_3__ {int rl; } ;
struct seq_softc {int unit; int timerbase; int midi_number; int out_water; int pre_event_timeout; int /*<<< orphan*/  seq_lock; TYPE_2__ out_q; int /*<<< orphan*/ * midi_flags; int /*<<< orphan*/  music; TYPE_1__ in_q; } ;
struct midi_info {int device; float* name; int dev_type; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  synth_type; } ;
struct cdev {struct seq_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EV_SZ ; 
 int EV_TIMING ; 
 int /*<<< orphan*/  LOOKUP_OPEN ; 
 int /*<<< orphan*/  MIDIMKDEV (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_SIZE (TYPE_2__) ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RANGE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,...) ; 
#define  SNDCTL_FM_4OP_ENABLE 155 
#define  SNDCTL_MIDI_INFO 154 
#define  SNDCTL_MIDI_PRETIME 153 
#define  SNDCTL_PMGR_ACCESS 152 
#define  SNDCTL_PMGR_IFACE 151 
#define  SNDCTL_SEQ_CTRLRATE 150 
#define  SNDCTL_SEQ_GETINCOUNT 149 
#define  SNDCTL_SEQ_GETOUTCOUNT 148 
#define  SNDCTL_SEQ_GETTIME 147 
#define  SNDCTL_SEQ_NRMIDIS 146 
#define  SNDCTL_SEQ_NRSYNTHS 145 
#define  SNDCTL_SEQ_OUTOFBAND 144 
#define  SNDCTL_SEQ_PANIC 143 
#define  SNDCTL_SEQ_RESET 142 
#define  SNDCTL_SEQ_RESETSAMPLES 141 
#define  SNDCTL_SEQ_SYNC 140 
#define  SNDCTL_SEQ_TESTMIDI 139 
#define  SNDCTL_SEQ_THRESHOLD 138 
#define  SNDCTL_SYNTH_INFO 137 
#define  SNDCTL_SYNTH_MEMAVL 136 
#define  SNDCTL_TMR_CONTINUE 135 
#define  SNDCTL_TMR_METRONOME 134 
#define  SNDCTL_TMR_SELECT 133 
#define  SNDCTL_TMR_SOURCE 132 
#define  SNDCTL_TMR_START 131 
#define  SNDCTL_TMR_STOP 130 
#define  SNDCTL_TMR_TEMPO 129 
#define  SNDCTL_TMR_TIMEBASE 128 
 int /*<<< orphan*/  SND_DEV_MIDIN ; 
 int /*<<< orphan*/  SYNTH_TYPE_MIDI ; 
 int TMR_CONTINUE ; 
 int TMR_START ; 
 int TMR_STOP ; 
 int TMR_TEMPO ; 
 int TMR_TIMERBASE ; 
 int /*<<< orphan*/  bzero (struct synth_info*,int) ; 
 int /*<<< orphan*/  cmdtab_seqioctl ; 
 int hz ; 
 int lookup_mididev (struct seq_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major (struct cdev*) ; 
 char* midi_cmdname (int,int /*<<< orphan*/ ) ; 
 int midi_ioctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,struct thread*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  seq_convertold (int*,int*) ; 
 int /*<<< orphan*/  seq_fetch_mid (struct seq_softc*,int,int /*<<< orphan*/ *) ; 
 int seq_processevent (struct seq_softc*,int*) ; 
 int /*<<< orphan*/  seq_reset (struct seq_softc*) ; 
 int seq_sync (struct seq_softc*) ; 
 int timer_now (struct seq_softc*) ; 

int
mseq_ioctl(struct cdev *i_dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{
	int midiunit, ret, tmp;
	struct seq_softc *scp = i_dev->si_drv1;
	struct synth_info *synthinfo;
	struct midi_info *midiinfo;
	u_char event[EV_SZ];
	u_char newevent[EV_SZ];

	kobj_t md;

	/*
	 * struct snd_size *sndsize;
	 */

	if (scp == NULL)
		return ENXIO;

	SEQ_DEBUG(6, printf("seq_ioctl: unit %d, cmd %s.\n",
	    scp->unit, midi_cmdname(cmd, cmdtab_seqioctl)));

	ret = 0;

	switch (cmd) {
	case SNDCTL_SEQ_GETTIME:
		/*
		 * ioctl needed by libtse
		 */
		mtx_lock(&scp->seq_lock);
		*(int *)arg = timer_now(scp);
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(6, printf("seq_ioctl: gettime %d.\n", *(int *)arg));
		ret = 0;
		break;
	case SNDCTL_TMR_METRONOME:
		/* fallthrough */
	case SNDCTL_TMR_SOURCE:
		/*
		 * Not implemented
		 */
		ret = 0;
		break;
	case SNDCTL_TMR_TEMPO:
		event[1] = TMR_TEMPO;
		event[4] = *(int *)arg & 0xFF;
		event[5] = (*(int *)arg >> 8) & 0xFF;
		event[6] = (*(int *)arg >> 16) & 0xFF;
		event[7] = (*(int *)arg >> 24) & 0xFF;
		goto timerevent;
	case SNDCTL_TMR_TIMEBASE:
		event[1] = TMR_TIMERBASE;
		event[4] = *(int *)arg & 0xFF;
		event[5] = (*(int *)arg >> 8) & 0xFF;
		event[6] = (*(int *)arg >> 16) & 0xFF;
		event[7] = (*(int *)arg >> 24) & 0xFF;
		goto timerevent;
	case SNDCTL_TMR_START:
		event[1] = TMR_START;
		goto timerevent;
	case SNDCTL_TMR_STOP:
		event[1] = TMR_STOP;
		goto timerevent;
	case SNDCTL_TMR_CONTINUE:
		event[1] = TMR_CONTINUE;
timerevent:
		event[0] = EV_TIMING;
		mtx_lock(&scp->seq_lock);
		if (!scp->music) {
			ret = EINVAL;
			mtx_unlock(&scp->seq_lock);
			break;
		}
		seq_processevent(scp, event);
		mtx_unlock(&scp->seq_lock);
		break;
	case SNDCTL_TMR_SELECT:
		SEQ_DEBUG(2,
		    printf("seq_ioctl: SNDCTL_TMR_SELECT not supported\n"));
		ret = EINVAL;
		break;
	case SNDCTL_SEQ_SYNC:
		if (mode == O_RDONLY) {
			ret = 0;
			break;
		}
		mtx_lock(&scp->seq_lock);
		ret = seq_sync(scp);
		mtx_unlock(&scp->seq_lock);
		break;
	case SNDCTL_SEQ_PANIC:
		/* fallthrough */
	case SNDCTL_SEQ_RESET:
		/*
		 * SNDCTL_SEQ_PANIC == SNDCTL_SEQ_RESET
		 */
		mtx_lock(&scp->seq_lock);
		seq_reset(scp);
		mtx_unlock(&scp->seq_lock);
		ret = 0;
		break;
	case SNDCTL_SEQ_TESTMIDI:
		mtx_lock(&scp->seq_lock);
		/*
		 * TODO: SNDCTL_SEQ_TESTMIDI now means "can I write to the
		 * device?".
		 */
		mtx_unlock(&scp->seq_lock);
		break;
#if 0
	case SNDCTL_SEQ_GETINCOUNT:
		if (mode == O_WRONLY)
			*(int *)arg = 0;
		else {
			mtx_lock(&scp->seq_lock);
			*(int *)arg = scp->in_q.rl;
			mtx_unlock(&scp->seq_lock);
			SEQ_DEBUG(printf("seq_ioctl: incount %d.\n",
			    *(int *)arg));
		}
		ret = 0;
		break;
	case SNDCTL_SEQ_GETOUTCOUNT:
		if (mode == O_RDONLY)
			*(int *)arg = 0;
		else {
			mtx_lock(&scp->seq_lock);
			*(int *)arg = scp->out_q.fl;
			mtx_unlock(&scp->seq_lock);
			SEQ_DEBUG(printf("seq_ioctl: outcount %d.\n",
			    *(int *)arg));
		}
		ret = 0;
		break;
#endif
	case SNDCTL_SEQ_CTRLRATE:
		if (*(int *)arg != 0) {
			ret = EINVAL;
			break;
		}
		mtx_lock(&scp->seq_lock);
		*(int *)arg = scp->timerbase;
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(3, printf("seq_ioctl: ctrlrate %d.\n", *(int *)arg));
		ret = 0;
		break;
		/*
		 * TODO: ioctl SNDCTL_SEQ_RESETSAMPLES
		 */
#if 0
	case SNDCTL_SEQ_RESETSAMPLES:
		mtx_lock(&scp->seq_lock);
		ret = lookup_mididev(scp, *(int *)arg, LOOKUP_OPEN, &md);
		mtx_unlock(&scp->seq_lock);
		if (ret != 0)
			break;
		ret = midi_ioctl(MIDIMKDEV(major(i_dev), *(int *)arg,
		    SND_DEV_MIDIN), cmd, arg, mode, td);
		break;
#endif
	case SNDCTL_SEQ_NRSYNTHS:
		mtx_lock(&scp->seq_lock);
		*(int *)arg = scp->midi_number;
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(3, printf("seq_ioctl: synths %d.\n", *(int *)arg));
		ret = 0;
		break;
	case SNDCTL_SEQ_NRMIDIS:
		mtx_lock(&scp->seq_lock);
		if (scp->music)
			*(int *)arg = 0;
		else {
			/*
		         * TODO: count the numbder of devices that can WRITERAW
		         */
			*(int *)arg = scp->midi_number;
		}
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(3, printf("seq_ioctl: midis %d.\n", *(int *)arg));
		ret = 0;
		break;
		/*
		 * TODO: ioctl SNDCTL_SYNTH_MEMAVL
		 */
#if 0
	case SNDCTL_SYNTH_MEMAVL:
		mtx_lock(&scp->seq_lock);
		ret = lookup_mididev(scp, *(int *)arg, LOOKUP_OPEN, &md);
		mtx_unlock(&scp->seq_lock);
		if (ret != 0)
			break;
		ret = midi_ioctl(MIDIMKDEV(major(i_dev), *(int *)arg,
		    SND_DEV_MIDIN), cmd, arg, mode, td);
		break;
#endif
	case SNDCTL_SEQ_OUTOFBAND:
		for (ret = 0; ret < EV_SZ; ret++)
			event[ret] = (u_char)arg[0];

		mtx_lock(&scp->seq_lock);
		if (scp->music)
			ret = seq_processevent(scp, event);
		else {
			if (seq_convertold(event, newevent) > 0)
				ret = seq_processevent(scp, newevent);
			else
				ret = EINVAL;
		}
		mtx_unlock(&scp->seq_lock);
		break;
	case SNDCTL_SYNTH_INFO:
		synthinfo = (struct synth_info *)arg;
		midiunit = synthinfo->device;
		mtx_lock(&scp->seq_lock);
		if (seq_fetch_mid(scp, midiunit, &md) == 0) {
			bzero(synthinfo, sizeof(*synthinfo));
			synthinfo->name[0] = 'f';
			synthinfo->name[1] = 'a';
			synthinfo->name[2] = 'k';
			synthinfo->name[3] = 'e';
			synthinfo->name[4] = 's';
			synthinfo->name[5] = 'y';
			synthinfo->name[6] = 'n';
			synthinfo->name[7] = 't';
			synthinfo->name[8] = 'h';
			synthinfo->device = midiunit;
			synthinfo->synth_type = SYNTH_TYPE_MIDI;
			synthinfo->capabilities = scp->midi_flags[midiunit];
			ret = 0;
		} else
			ret = EINVAL;
		mtx_unlock(&scp->seq_lock);
		break;
	case SNDCTL_MIDI_INFO:
		midiinfo = (struct midi_info *)arg;
		midiunit = midiinfo->device;
		mtx_lock(&scp->seq_lock);
		if (seq_fetch_mid(scp, midiunit, &md) == 0) {
			bzero(midiinfo, sizeof(*midiinfo));
			midiinfo->name[0] = 'f';
			midiinfo->name[1] = 'a';
			midiinfo->name[2] = 'k';
			midiinfo->name[3] = 'e';
			midiinfo->name[4] = 'm';
			midiinfo->name[5] = 'i';
			midiinfo->name[6] = 'd';
			midiinfo->name[7] = 'i';
			midiinfo->device = midiunit;
			midiinfo->capabilities = scp->midi_flags[midiunit];
			/*
		         * TODO: What devtype?
		         */
			midiinfo->dev_type = 0x01;
			ret = 0;
		} else
			ret = EINVAL;
		mtx_unlock(&scp->seq_lock);
		break;
	case SNDCTL_SEQ_THRESHOLD:
		mtx_lock(&scp->seq_lock);
		RANGE(*(int *)arg, 1, MIDIQ_SIZE(scp->out_q) - 1);
		scp->out_water = *(int *)arg;
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(3, printf("seq_ioctl: water %d.\n", *(int *)arg));
		ret = 0;
		break;
	case SNDCTL_MIDI_PRETIME:
		tmp = *(int *)arg;
		if (tmp < 0)
			tmp = 0;
		mtx_lock(&scp->seq_lock);
		scp->pre_event_timeout = (hz * tmp) / 10;
		*(int *)arg = scp->pre_event_timeout;
		mtx_unlock(&scp->seq_lock);
		SEQ_DEBUG(3, printf("seq_ioctl: pretime %d.\n", *(int *)arg));
		ret = 0;
		break;
	case SNDCTL_FM_4OP_ENABLE:
	case SNDCTL_PMGR_IFACE:
	case SNDCTL_PMGR_ACCESS:
		/*
		 * Patch manager and fm are ded, ded, ded.
		 */
		/* fallthrough */
	default:
		/*
		 * TODO: Consider ioctl default case.
		 * Old code used to
		 * if ((scp->fflags & O_ACCMODE) == FREAD) {
		 *	ret = EIO;
		 *	break;
		 * }
		 * Then pass on the ioctl to device 0
		 */
		SEQ_DEBUG(2,
		    printf("seq_ioctl: unsupported IOCTL %ld.\n", cmd));
		ret = EINVAL;
		break;
	}

	return ret;
}