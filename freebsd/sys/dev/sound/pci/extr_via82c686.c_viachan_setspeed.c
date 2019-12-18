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
typedef  int u_int32_t ;
struct via_info {int codec_caps; int /*<<< orphan*/  codec; } ;
struct via_chinfo {scalar_t__ dir; struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AC97_EXTCAP_VRA ; 
 int AC97_REGEXT_FDACRATE ; 
 int AC97_REGEXT_LADCRATE ; 
 scalar_t__ PCMDIR_PLAY ; 
 int ac97_setrate (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
viachan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;
	int reg;

	/*
	 *  Basic AC'97 defines a 48 kHz sample rate only.  For other rates,
	 *  upsampling is required.
	 *
	 *  The VT82C686A does not perform upsampling, and neither do we.
	 *  If the codec supports variable-rate audio (i.e. does the upsampling
	 *  itself), then negotiate the rate with the codec.  Otherwise,
	 *  return 48 kHz cuz that's all you got.
	 */
	if (via->codec_caps & AC97_EXTCAP_VRA) {
		reg = (ch->dir == PCMDIR_PLAY)? AC97_REGEXT_FDACRATE : AC97_REGEXT_LADCRATE;
		return ac97_setrate(via->codec, reg, speed);
	} else
		return 48000;
}