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
typedef  size_t u16 ;
struct hostapd_hw_modes {int mode; } ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */

struct hostapd_hw_modes * get_mode(struct hostapd_hw_modes *modes,
				   u16 num_modes, enum hostapd_hw_mode mode)
{
	u16 i;

	for (i = 0; i < num_modes; i++) {
		if (modes[i].mode == mode)
			return &modes[i];
	}

	return NULL;
}