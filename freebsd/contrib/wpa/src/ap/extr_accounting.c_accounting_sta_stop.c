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
struct sta_info {scalar_t__ acct_session_started; scalar_t__ acct_session_id; int /*<<< orphan*/  addr; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  accounting_interim_update ; 
 int /*<<< orphan*/  accounting_sta_report (struct hostapd_data*,struct sta_info*,int) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long) ; 

void accounting_sta_stop(struct hostapd_data *hapd, struct sta_info *sta)
{
	if (sta->acct_session_started) {
		accounting_sta_report(hapd, sta, 1);
		eloop_cancel_timeout(accounting_interim_update, hapd, sta);
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_RADIUS,
			       HOSTAPD_LEVEL_INFO,
			       "stopped accounting session %016llX",
			       (unsigned long long) sta->acct_session_id);
		sta->acct_session_started = 0;
	}
}