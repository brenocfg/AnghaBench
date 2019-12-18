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
struct ac97_info {int extcaps; TYPE_1__* mix; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int AC97_EXTCAP_SDAC ; 
 int /*<<< orphan*/  AC97_MIXEXT_SURROUND ; 
 int /*<<< orphan*/  AC97_MIX_AUXOUT ; 
 size_t SOUND_MIXER_OGAIN ; 
 int ac97_rdcd (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

__attribute__((used)) static void
ac97_fix_auxout(struct ac97_info *codec)
{
	int keep_ogain;

	/*
	 * By default, The ac97 aux_out register (0x04) corresponds to OSS's
	 * OGAIN setting.
	 *
	 * We first check whether aux_out is a valid register.  If not
	 * we may not want to keep ogain.
	 */
	keep_ogain = ac97_rdcd(codec, AC97_MIX_AUXOUT) & 0x8000;

	/*
	 * Determine what AUX_OUT really means, it can be:
	 *
	 * 1. Headphone out.
	 * 2. 4-Channel Out
	 * 3. True line level out (effectively master volume).
	 *
	 * See Sections 5.2.1 and 5.27 for AUX_OUT Options in AC97r2.{2,3}.
	 */
	if (codec->extcaps & AC97_EXTCAP_SDAC &&
	    ac97_rdcd(codec, AC97_MIXEXT_SURROUND) == 0x8080) {
		codec->mix[SOUND_MIXER_OGAIN].reg = AC97_MIXEXT_SURROUND;
		keep_ogain = 1;
	}

	if (keep_ogain == 0) {
		bzero(&codec->mix[SOUND_MIXER_OGAIN],
		      sizeof(codec->mix[SOUND_MIXER_OGAIN]));
	}
}