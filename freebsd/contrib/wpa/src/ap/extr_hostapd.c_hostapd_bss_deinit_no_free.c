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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  hostapd_clear_wep (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_flush_old_stations (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_free_stas (struct hostapd_data*) ; 

__attribute__((used)) static void hostapd_bss_deinit_no_free(struct hostapd_data *hapd)
{
	hostapd_free_stas(hapd);
	hostapd_flush_old_stations(hapd, WLAN_REASON_DEAUTH_LEAVING);
	hostapd_clear_wep(hapd);
}