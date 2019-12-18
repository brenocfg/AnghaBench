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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wnm_bss_keep_alive ; 

void wnm_bss_keep_alive_deinit(struct wpa_supplicant *wpa_s)
{
#ifdef CONFIG_WNM
	eloop_cancel_timeout(wnm_bss_keep_alive, wpa_s, NULL);
#endif /* CONFIG_WNM */
}