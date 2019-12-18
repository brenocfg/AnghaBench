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
struct sta_info {int acct_interim_interval; } ;
struct hostapd_data {int dummy; } ;
struct hostap_sta_driver_data {int dummy; } ;

/* Variables and functions */
 int ACCT_DEFAULT_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  accounting_sta_interim (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  accounting_sta_update_stats (struct hostapd_data*,struct sta_info*,struct hostap_sta_driver_data*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,void (*) (void*,void*),struct hostapd_data*,struct sta_info*) ; 

__attribute__((used)) static void accounting_interim_update(void *eloop_ctx, void *timeout_ctx)
{
	struct hostapd_data *hapd = eloop_ctx;
	struct sta_info *sta = timeout_ctx;
	int interval;

	if (sta->acct_interim_interval) {
		accounting_sta_interim(hapd, sta);
		interval = sta->acct_interim_interval;
	} else {
		struct hostap_sta_driver_data data;
		accounting_sta_update_stats(hapd, sta, &data);
		interval = ACCT_DEFAULT_UPDATE_INTERVAL;
	}

	eloop_register_timeout(interval, 0, accounting_interim_update,
			       hapd, sta);
}