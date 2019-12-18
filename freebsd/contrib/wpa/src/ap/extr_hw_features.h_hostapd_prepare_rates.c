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
struct hostapd_iface {int dummy; } ;
struct hostapd_hw_modes {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int hostapd_prepare_rates(struct hostapd_iface *iface,
					struct hostapd_hw_modes *mode)
{
	return 0;
}