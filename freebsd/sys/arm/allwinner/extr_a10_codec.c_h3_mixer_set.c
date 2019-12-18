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
struct a10codec_info {int dummy; } ;
struct TYPE_2__ {unsigned int mask; unsigned int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 TYPE_1__* h3_mixers ; 
 int /*<<< orphan*/  h3_pr_set_clear (struct a10codec_info*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct a10codec_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
h3_mixer_set(struct snd_mixer *m, unsigned dev, unsigned left,
    unsigned right)
{
	struct a10codec_info *sc = mix_getdevinfo(m);
	unsigned nvol, max;

	max = h3_mixers[dev].mask >> h3_mixers[dev].shift;
	nvol = (left * max) / 100;

	h3_pr_set_clear(sc, h3_mixers[dev].reg,
	    nvol << h3_mixers[dev].shift, h3_mixers[dev].mask);

	left = right = (left * 100) / max;
	return (left | (right << 8));
}