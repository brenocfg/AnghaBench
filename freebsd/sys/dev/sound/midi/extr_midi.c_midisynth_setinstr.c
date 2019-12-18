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
 int midi_instroff ; 
 int midisynth_writeraw (void*,int*,int) ; 

__attribute__((used)) static int
midisynth_setinstr(void *n, uint8_t chn, uint16_t instr)
{
	u_char c[2];

	if (instr > 127 || chn > 15)
		return EINVAL;

	c[0] = 0xc0 | (chn & 0x0f);	/* Progamme change. */
	c[1] = instr + midi_instroff;

	return midisynth_writeraw(n, c, 2);
}