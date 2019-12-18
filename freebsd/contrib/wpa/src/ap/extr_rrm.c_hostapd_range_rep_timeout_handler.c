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
struct hostapd_data {scalar_t__ range_req_active; int /*<<< orphan*/  range_req_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_range_rep_timeout_handler(void *eloop_data, void *user_ctx)
{
	struct hostapd_data *hapd = eloop_data;

	wpa_printf(MSG_DEBUG, "RRM: Range request (token %u) timed out",
		   hapd->range_req_token);
	hapd->range_req_active = 0;
}