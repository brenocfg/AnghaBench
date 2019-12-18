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
struct wpa_supplicant {scalar_t__ coloc_intf_auto_report; scalar_t__ coloc_intf_dialog_token; } ;

/* Variables and functions */

void wnm_clear_coloc_intf_reporting(struct wpa_supplicant *wpa_s)
{
#ifdef CONFIG_WNM
	wpa_s->coloc_intf_dialog_token = 0;
	wpa_s->coloc_intf_auto_report = 0;
#endif /* CONFIG_WNM */
}