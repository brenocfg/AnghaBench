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
struct emu_voice {int b16; int stereo; int speed; TYPE_1__* slave; } ;
struct TYPE_2__ {int b16; int stereo; int speed; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 

void
emu_vsetup(struct emu_voice *v, int fmt, int spd)
{
	if (fmt) {
		v->b16 = (fmt & AFMT_16BIT) ? 1 : 0;
		v->stereo = (AFMT_CHANNEL(fmt) > 1) ? 1 : 0;
		if (v->slave != NULL) {
			v->slave->b16 = v->b16;
			v->slave->stereo = v->stereo;
		}
	}
	if (spd) {
		v->speed = spd;
		if (v->slave != NULL)
			v->slave->speed = v->speed;
	}
}