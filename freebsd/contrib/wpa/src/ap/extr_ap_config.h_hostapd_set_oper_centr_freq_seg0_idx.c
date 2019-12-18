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
typedef  void* u8 ;
struct hostapd_config {void* vht_oper_centr_freq_seg0_idx; void* he_oper_centr_freq_seg0_idx; scalar_t__ ieee80211ax; } ;

/* Variables and functions */

__attribute__((used)) static inline void
hostapd_set_oper_centr_freq_seg0_idx(struct hostapd_config *conf,
				     u8 oper_centr_freq_seg0_idx)
{
#ifdef CONFIG_IEEE80211AX
	if (conf->ieee80211ax)
		conf->he_oper_centr_freq_seg0_idx = oper_centr_freq_seg0_idx;
#endif /* CONFIG_IEEE80211AX */
	conf->vht_oper_centr_freq_seg0_idx = oper_centr_freq_seg0_idx;
}