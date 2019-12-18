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
typedef  int u_int32_t ;
struct TYPE_2__ {char* strings; int* strindex; int nvalues; } ;
struct snd_mixer {int recdevs; int /*<<< orphan*/  dev; TYPE_1__ enuminfo; } ;
typedef  TYPE_1__ oss_mixer_enuminfo ;

/* Variables and functions */
 int OSS_ENUM_MAXVALUE ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * snd_mixernames ; 
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 

void
mix_setrecdevs(struct snd_mixer *m, u_int32_t v)
{
	oss_mixer_enuminfo *ei;
	char *loc;
	int i, nvalues, nwrote, nleft, ncopied;

	ei = &m->enuminfo;

	nvalues = 0;
	nwrote = 0;
	nleft = sizeof(ei->strings);
	loc = ei->strings;

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if ((1 << i) & v) {
			ei->strindex[nvalues] = nwrote;
			ncopied = strlcpy(loc, snd_mixernames[i], nleft) + 1;
			    /* strlcpy retval doesn't include terminator */

			nwrote += ncopied;
			nleft -= ncopied;
			nvalues++;

			/*
			 * XXX I don't think this should ever be possible.
			 * Even with a move to dynamic device/channel names,
			 * each label is limited to ~16 characters, so that'd
			 * take a LOT to fill this buffer.
			 */
			if ((nleft <= 0) || (nvalues >= OSS_ENUM_MAXVALUE)) {
				device_printf(m->dev,
				    "mix_setrecdevs:  Not enough room to store device names--please file a bug report.\n");
				device_printf(m->dev, 
				    "mix_setrecdevs:  Please include details about your sound hardware, OS version, etc.\n");
				break;
			}

			loc = &ei->strings[nwrote];
		}
	}

	/*
	 * NB:	The SNDCTL_DSP_GET_RECSRC_NAMES ioctl ignores the dev
	 * 	and ctrl fields.
	 */
	ei->nvalues = nvalues;
	m->recdevs = v;
}