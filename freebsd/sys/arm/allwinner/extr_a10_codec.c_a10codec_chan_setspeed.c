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
typedef  int uint32_t ;
struct a10codec_chinfo {int speed; int /*<<< orphan*/  dir; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMDIR_PLAY ; 

__attribute__((used)) static uint32_t
a10codec_chan_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct a10codec_chinfo *ch = data;

	/*
	 * The codec supports full duplex operation but both DAC and ADC
	 * use the same source clock (PLL2). Limit the available speeds to
	 * those supported by a 24576000 Hz input.
	 */
	switch (speed) {
	case 8000:
	case 12000:
	case 16000:
	case 24000:
	case 32000:
	case 48000:
		ch->speed = speed;
		break;
	case 96000:
	case 192000:
		/* 96 KHz / 192 KHz mode only supported for playback */
		if (ch->dir == PCMDIR_PLAY) {
			ch->speed = speed;
		} else {
			ch->speed = 48000;
		}
		break;
	case 44100:
		ch->speed = 48000;
		break;
	case 22050:
		ch->speed = 24000;
		break;
	case 11025:
		ch->speed = 12000;
		break;
	default:
		ch->speed = 48000;
		break;
	}

	return (ch->speed);
}