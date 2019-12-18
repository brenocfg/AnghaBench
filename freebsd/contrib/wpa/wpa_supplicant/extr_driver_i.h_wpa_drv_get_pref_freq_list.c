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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; scalar_t__ get_pref_freq_list_override; } ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;
struct TYPE_2__ {int (* get_pref_freq_list ) (int /*<<< orphan*/ ,int,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,unsigned int*,unsigned int*) ; 
 int wpas_ctrl_iface_get_pref_freq_list_override (struct wpa_supplicant*,int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static inline int wpa_drv_get_pref_freq_list(struct wpa_supplicant *wpa_s,
					     enum wpa_driver_if_type if_type,
					     unsigned int *num,
					     unsigned int *freq_list)
{
#ifdef CONFIG_TESTING_OPTIONS
	if (wpa_s->get_pref_freq_list_override)
		return wpas_ctrl_iface_get_pref_freq_list_override(
			wpa_s, if_type, num, freq_list);
#endif /* CONFIG_TESTING_OPTIONS */
	if (!wpa_s->driver->get_pref_freq_list)
		return -1;
	return wpa_s->driver->get_pref_freq_list(wpa_s->drv_priv, if_type,
						 num, freq_list);
}