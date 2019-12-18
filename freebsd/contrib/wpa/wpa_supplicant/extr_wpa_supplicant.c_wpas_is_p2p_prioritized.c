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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {scalar_t__ conc_pref; } ;

/* Variables and functions */
 scalar_t__ WPA_CONC_PREF_P2P ; 
 scalar_t__ WPA_CONC_PREF_STA ; 

int wpas_is_p2p_prioritized(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->global->conc_pref == WPA_CONC_PREF_P2P)
		return 1;
	if (wpa_s->global->conc_pref == WPA_CONC_PREF_STA)
		return 0;
	return -1;
}