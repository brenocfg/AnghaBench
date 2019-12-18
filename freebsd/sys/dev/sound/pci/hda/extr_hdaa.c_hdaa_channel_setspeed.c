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
struct hdaa_chan {int* pcmrates; int spd; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
hdaa_channel_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct hdaa_chan *ch = data;
	uint32_t spd = 0, threshold;
	int i;

	/* First look for equal or multiple frequency. */
	for (i = 0; ch->pcmrates[i] != 0; i++) {
		spd = ch->pcmrates[i];
		if (speed != 0 && spd / speed * speed == spd) {
			ch->spd = spd;
			return (spd);
		}
	}
	/* If no match, just find nearest. */
	for (i = 0; ch->pcmrates[i] != 0; i++) {
		spd = ch->pcmrates[i];
		threshold = spd + ((ch->pcmrates[i + 1] != 0) ?
		    ((ch->pcmrates[i + 1] - spd) >> 1) : 0);
		if (speed < threshold)
			break;
	}
	ch->spd = spd;
	return (spd);
}