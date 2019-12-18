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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ freq_start; scalar_t__ freq_end; } ;

/* Variables and functions */
 TYPE_1__* vht80_chan_ranges ; 

__attribute__((used)) static int
is_vht80_valid_freq(uint16_t freq)
{
	int i;
	for (i = 0; vht80_chan_ranges[i].freq_start != 0; i++) {
		if (freq >= vht80_chan_ranges[i].freq_start &&
		    freq < vht80_chan_ranges[i].freq_end)
			return (1);
	}
	return (0);
}