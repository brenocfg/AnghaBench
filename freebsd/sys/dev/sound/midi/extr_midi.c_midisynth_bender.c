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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int midisynth_writeraw (void*,int*,int) ; 

__attribute__((used)) static int
midisynth_bender(void *n, uint8_t chn, uint16_t val)
{
	u_char c[3];


	if (val > 16383 || chn > 15)
		return EINVAL;

	c[0] = 0xe0 | (chn & 0x0f);	/* Pitch bend. */
	c[1] = (u_char)val & 0x7f;
	c[2] = (u_char)(val >> 7) & 0x7f;

	return midisynth_writeraw(n, c, 3);
}