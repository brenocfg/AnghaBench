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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {int /*<<< orphan*/  radius; int /*<<< orphan*/  acct_session_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_ACCT ; 
 int /*<<< orphan*/  accounting_interim_error_cb ; 
 int /*<<< orphan*/  accounting_receive ; 
 int /*<<< orphan*/  accounting_report_state (struct hostapd_data*,int) ; 
 scalar_t__ radius_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*) ; 
 int /*<<< orphan*/  radius_client_set_interim_error_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*) ; 
 scalar_t__ radius_gen_session_id (int /*<<< orphan*/ *,int) ; 

int accounting_init(struct hostapd_data *hapd)
{
	if (radius_gen_session_id((u8 *) &hapd->acct_session_id,
				  sizeof(hapd->acct_session_id)) < 0)
		return -1;

	if (radius_client_register(hapd->radius, RADIUS_ACCT,
				   accounting_receive, hapd))
		return -1;
	radius_client_set_interim_error_cb(hapd->radius,
					   accounting_interim_error_cb, hapd);

	accounting_report_state(hapd, 1);

	return 0;
}