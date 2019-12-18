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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct hostapd_freq_params {int dummy; } ;
struct TYPE_2__ {int (* tdls_enable_channel_switch ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct hostapd_freq_params const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct hostapd_freq_params const*) ; 

__attribute__((used)) static inline int wpa_drv_tdls_enable_channel_switch(
	struct wpa_supplicant *wpa_s, const u8 *addr, u8 oper_class,
	const struct hostapd_freq_params *freq_params)
{
	if (!wpa_s->driver->tdls_enable_channel_switch)
		return -1;
	return wpa_s->driver->tdls_enable_channel_switch(wpa_s->drv_priv, addr,
							 oper_class,
							 freq_params);
}