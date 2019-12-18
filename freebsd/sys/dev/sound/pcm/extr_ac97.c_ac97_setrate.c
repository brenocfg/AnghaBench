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
typedef  int u_int16_t ;
struct ac97_info {int extstat; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AC97_EXTCAP_DRA ; 
#define  AC97_REGEXT_FDACRATE 132 
#define  AC97_REGEXT_LADCRATE 131 
#define  AC97_REGEXT_LDACRATE 130 
#define  AC97_REGEXT_MADCRATE 129 
#define  AC97_REGEXT_SDACRATE 128 
 int ac97_rdcd (struct ac97_info*,int) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

int
ac97_setrate(struct ac97_info *codec, int which, int rate)
{
	u_int16_t v;

	switch(which) {
	case AC97_REGEXT_FDACRATE:
	case AC97_REGEXT_SDACRATE:
	case AC97_REGEXT_LDACRATE:
	case AC97_REGEXT_LADCRATE:
	case AC97_REGEXT_MADCRATE:
		break;

	default:
		return -1;
	}

	snd_mtxlock(codec->lock);
	if (rate != 0) {
		v = rate;
		if (codec->extstat & AC97_EXTCAP_DRA)
			v >>= 1;
		ac97_wrcd(codec, which, v);
	}
	v = ac97_rdcd(codec, which);
	if (codec->extstat & AC97_EXTCAP_DRA)
		v <<= 1;
	snd_mtxunlock(codec->lock);
	return v;
}