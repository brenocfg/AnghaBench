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
typedef  int uint16_t ;
struct hdaa_chan {int fmt; int bit16; int bit32; scalar_t__ spd; } ;
struct TYPE_2__ {scalar_t__ rate; int base; int mul; int div; scalar_t__ valid; } ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S16_LE ; 
 int AFMT_S32_LE ; 
 int HDA_RATE_TAB_LEN ; 
 TYPE_1__* hda_rate_tab ; 

__attribute__((used)) static uint16_t
hdaa_stream_format(struct hdaa_chan *ch)
{
	int i;
	uint16_t fmt;

	fmt = 0;
	if (ch->fmt & AFMT_S16_LE)
		fmt |= ch->bit16 << 4;
	else if (ch->fmt & AFMT_S32_LE)
		fmt |= ch->bit32 << 4;
	else
		fmt |= 1 << 4;
	for (i = 0; i < HDA_RATE_TAB_LEN; i++) {
		if (hda_rate_tab[i].valid && ch->spd == hda_rate_tab[i].rate) {
			fmt |= hda_rate_tab[i].base;
			fmt |= hda_rate_tab[i].mul;
			fmt |= hda_rate_tab[i].div;
			break;
		}
	}
	fmt |= (AFMT_CHANNEL(ch->fmt) - 1);

	return (fmt);
}