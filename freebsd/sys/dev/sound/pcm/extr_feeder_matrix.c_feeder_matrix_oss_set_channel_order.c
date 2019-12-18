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
typedef  int uint32_t ;
struct pcmchan_matrix {int mask; int channels; scalar_t__ ext; size_t* offset; TYPE_1__* map; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_CHN_OSS_BEGIN ; 
 int SND_CHN_OSS_END ; 
 int SND_CHN_OSS_MAX ; 
 int SND_CHN_OSS_VALIDMASK ; 
 int SND_CHN_T_MASK_LF ; 
 int SND_CHN_T_MAX ; 
 int /*<<< orphan*/  memset (size_t*,int,int) ; 
 int* oss_to_snd_chn ; 

int
feeder_matrix_oss_set_channel_order(struct pcmchan_matrix *m,
    unsigned long long *map)
{
	struct pcmchan_matrix tmp;
	uint32_t chmask, i;
	int ch, cheof;

	if (m == NULL || map == NULL || (m->mask & ~SND_CHN_OSS_VALIDMASK) ||
	    m->channels > SND_CHN_OSS_MAX || (*map & 0xffffffff00000000ULL))
		return (EINVAL);

	tmp = *m;
	tmp.channels = 0;
	tmp.ext = 0;
	tmp.mask = 0;
	memset(tmp.offset, -1, sizeof(tmp.offset));
	cheof = 0;

	for (i = 0; i < SND_CHN_OSS_MAX; i++) {
		ch = (*map >> (i * 4)) & 0xf;
		if (ch < SND_CHN_OSS_BEGIN) {
			if (cheof == 0 && m->map[i].type != SND_CHN_T_MAX)
				return (EINVAL);
			cheof++;
			tmp.map[i] = m->map[i];
			continue;
		} else if (ch > SND_CHN_OSS_END)
			return (EINVAL);
		else if (cheof != 0)
			return (EINVAL);
		ch = oss_to_snd_chn[ch];
		chmask = 1 << ch;
		/* channel not exist in matrix */
		if (!(chmask & m->mask))
			return (EINVAL);
		/* duplicated channel */
		if (chmask & tmp.mask)
			return (EINVAL);
		tmp.map[i] = m->map[m->offset[ch]];
		if (tmp.map[i].type != ch)
			return (EINVAL);
		tmp.offset[ch] = i;
		tmp.mask |= chmask;
		tmp.channels++;
		if (chmask & SND_CHN_T_MASK_LF)
			tmp.ext++;
	}

	if (tmp.channels != m->channels || tmp.ext != m->ext ||
	    tmp.mask != m->mask ||
	    tmp.map[m->channels].type != SND_CHN_T_MAX)
		return (EINVAL);

	*m = tmp;

	return (0);
}