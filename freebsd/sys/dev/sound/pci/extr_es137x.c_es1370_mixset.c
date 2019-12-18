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
struct snd_mixer {int dummy; } ;
struct es_info {int /*<<< orphan*/  escfg; } ;
struct TYPE_2__ {int left; int right; scalar_t__ stereo; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 scalar_t__ ES_DAC1_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 scalar_t__ ES_SINGLE_PCM_MIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 unsigned int SOUND_MIXER_PCM ; 
 size_t SOUND_MIXER_SYNTH ; 
 int /*<<< orphan*/  es1370_wrcodec (struct es_info*,int,int) ; 
 struct es_info* mix_getdevinfo (struct snd_mixer*) ; 
 TYPE_1__* mixtable ; 

__attribute__((used)) static int
es1370_mixset(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct es_info *es;
	int l, r, rl, rr, set_dac1;

	if (!mixtable[dev].avail)
		return (-1);
	l = left;
	r = (mixtable[dev].stereo) ? right : l;
	if (mixtable[dev].left == 0xf)
		rl = (l < 2) ? 0x80 : 7 - (l - 2) / 14;
	else
		rl = (l < 7) ? 0x80 : 31 - (l - 7) / 3;
	es = mix_getdevinfo(m);
	ES_LOCK(es);
	if (dev == SOUND_MIXER_PCM && (ES_SINGLE_PCM_MIX(es->escfg)) &&
	    ES_DAC1_ENABLED(es->escfg))
		set_dac1 = 1;
	else
		set_dac1 = 0;
	if (mixtable[dev].stereo) {
		rr = (r < 7) ? 0x80 : 31 - (r - 7) / 3;
		es1370_wrcodec(es, mixtable[dev].right, rr);
		if (set_dac1 && mixtable[SOUND_MIXER_SYNTH].stereo)
			es1370_wrcodec(es,
			    mixtable[SOUND_MIXER_SYNTH].right, rr);
	}
	es1370_wrcodec(es, mixtable[dev].left, rl);
	if (set_dac1)
		es1370_wrcodec(es, mixtable[SOUND_MIXER_SYNTH].left, rl);
	ES_UNLOCK(es);

	return (l | (r << 8));
}