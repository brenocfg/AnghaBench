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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct wpa_bss_trans_info {int dummy; } ;
struct wpa_bss_candidate_info {int dummy; } ;
struct TYPE_2__ {struct wpa_bss_candidate_info* (* get_bss_transition_status ) (int /*<<< orphan*/ ,struct wpa_bss_trans_info*) ;} ;

/* Variables and functions */
 struct wpa_bss_candidate_info* stub1 (int /*<<< orphan*/ ,struct wpa_bss_trans_info*) ; 

__attribute__((used)) static inline struct wpa_bss_candidate_info *
wpa_drv_get_bss_trans_status(struct wpa_supplicant *wpa_s,
			     struct wpa_bss_trans_info *params)
{
	if (!wpa_s->driver->get_bss_transition_status)
		return NULL;
	return wpa_s->driver->get_bss_transition_status(wpa_s->drv_priv,
							params);
}