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
struct wmm_ac_addts_request {int /*<<< orphan*/  tspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wmm_ac_del_req (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wmm_ac_get_tsid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmm_ac_get_user_priority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wmm_ac_addts_req_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct wmm_ac_addts_request *addts_req = timeout_ctx;

	wpa_printf(MSG_DEBUG,
		   "Timeout getting ADDTS response (tsid=%d up=%d)",
		   wmm_ac_get_tsid(&addts_req->tspec),
		   wmm_ac_get_user_priority(&addts_req->tspec));

	wmm_ac_del_req(wpa_s, 1);
}