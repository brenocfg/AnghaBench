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
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;

/* Variables and functions */

u_int16_t
pf_cksum_fixup(u_int16_t cksum, u_int16_t old, u_int16_t new, u_int8_t udp)
{
	u_int32_t	l;

	if (udp && !cksum)
		return (0x0000);
	l = cksum + old - new;
	l = (l >> 16) + (l & 65535);
	l = l & 65535;
	if (udp && !l)
		return (0xFFFF);
	return (l);
}