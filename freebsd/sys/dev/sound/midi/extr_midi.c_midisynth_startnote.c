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
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int midisynth_writeraw (void*,int*,int) ; 

__attribute__((used)) static int
midisynth_startnote(void *n, uint8_t chn, uint8_t note, uint8_t vel)
{
	u_char c[3];

	if (note > 127 || chn > 15)
		return EINVAL;

	if (vel > 127)
		vel = 127;

	c[0] = 0x90 | (chn & 0x0f);	/* Note on. */
	c[1] = (u_char)note;
	c[2] = (u_char)vel;

	return midisynth_writeraw(n, c, 3);
}