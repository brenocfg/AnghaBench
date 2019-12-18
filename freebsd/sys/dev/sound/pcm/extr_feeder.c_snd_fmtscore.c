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

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_24BIT ; 
 int AFMT_32BIT ; 
 int AFMT_8BIT ; 
 int AFMT_A_LAW ; 
 int AFMT_BIGENDIAN ; 
 int AFMT_CHANNEL (int) ; 
 int AFMT_MU_LAW ; 
 int AFMT_SIGNED ; 

u_int32_t
snd_fmtscore(u_int32_t fmt)
{
	u_int32_t ret;

	ret = 0;
	if (fmt & AFMT_SIGNED)
		ret |= 1 << 0;
	if (fmt & AFMT_BIGENDIAN)
		ret |= 1 << 1;
	/*if (fmt & AFMT_STEREO)
		ret |= (2 & 0x3f) << 2;
	else
		ret |= (1 & 0x3f) << 2;*/
	ret |= (AFMT_CHANNEL(fmt) & 0x3f) << 2;
	if (fmt & AFMT_A_LAW)
		ret |= 1 << 8;
	else if (fmt & AFMT_MU_LAW)
		ret |= 1 << 9;
	else if (fmt & AFMT_8BIT)
		ret |= 1 << 10;
	else if (fmt & AFMT_16BIT)
		ret |= 1 << 11;
	else if (fmt & AFMT_24BIT)
		ret |= 1 << 12;
	else if (fmt & AFMT_32BIT)
		ret |= 1 << 13;

	return ret;
}