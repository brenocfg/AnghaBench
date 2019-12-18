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
struct sta_info {int /*<<< orphan*/  acct_session_id; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int radius_gen_session_id (int /*<<< orphan*/ *,int) ; 

int accounting_sta_get_id(struct hostapd_data *hapd, struct sta_info *sta)
{
	return radius_gen_session_id((u8 *) &sta->acct_session_id,
				     sizeof(sta->acct_session_id));
}