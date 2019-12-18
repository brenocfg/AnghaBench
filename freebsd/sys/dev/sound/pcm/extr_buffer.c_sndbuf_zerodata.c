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
typedef  int u_int8_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 int AFMT_A_LAW ; 
 int AFMT_MU_LAW ; 
 int AFMT_PASSTHROUGH ; 
 int AFMT_SIGNED ; 

u_int8_t
sndbuf_zerodata(u_int32_t fmt)
{
	if (fmt & (AFMT_SIGNED | AFMT_PASSTHROUGH))
		return (0x00);
	else if (fmt & AFMT_MU_LAW)
		return (0x7f);
	else if (fmt & AFMT_A_LAW)
		return (0x55);
	return (0x80);
}