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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
#define  I40E_LINK_SPEED_100MB 133 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 

__attribute__((used)) static u8
ixl_convert_sysctl_aq_link_speed(u8 speeds, bool to_aq)
{
	static u16 speedmap[6] = {
		(I40E_LINK_SPEED_100MB | (0x1 << 8)),
		(I40E_LINK_SPEED_1GB   | (0x2 << 8)),
		(I40E_LINK_SPEED_10GB  | (0x4 << 8)),
		(I40E_LINK_SPEED_20GB  | (0x8 << 8)),
		(I40E_LINK_SPEED_25GB  | (0x10 << 8)),
		(I40E_LINK_SPEED_40GB  | (0x20 << 8))
	};
	u8 retval = 0;

	for (int i = 0; i < 6; i++) {
		if (to_aq)
			retval |= (speeds & (speedmap[i] >> 8)) ? (speedmap[i] & 0xff) : 0;
		else
			retval |= (speeds & speedmap[i]) ? (speedmap[i] >> 8) : 0;
	}

	return (retval);
}