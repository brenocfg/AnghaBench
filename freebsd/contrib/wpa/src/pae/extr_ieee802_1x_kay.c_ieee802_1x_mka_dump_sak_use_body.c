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
struct ieee802_1x_mka_sak_use_body {int lan; int oan; int /*<<< orphan*/  olpn; int /*<<< orphan*/  okn; int /*<<< orphan*/  osrv_mi; int /*<<< orphan*/  llpn; int /*<<< orphan*/  lkn; int /*<<< orphan*/  lsrv_mi; int /*<<< orphan*/  delay_protect; int /*<<< orphan*/  prx; int /*<<< orphan*/  ptx; int /*<<< orphan*/  orx; int /*<<< orphan*/  otx; int /*<<< orphan*/  lrx; int /*<<< orphan*/  ltx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int be_to_host32 (int /*<<< orphan*/ ) ; 
 int get_mka_param_body_len (struct ieee802_1x_mka_sak_use_body*) ; 
 int mi_txt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int yes_no (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee802_1x_mka_dump_sak_use_body(struct ieee802_1x_mka_sak_use_body *body)
{
	int body_len;

	if (body == NULL)
		return;

	/* IEEE Std 802.1X-2010, Figure 11-10 */
	body_len = get_mka_param_body_len(body);
	wpa_printf(MSG_DEBUG, "MACsec SAK Use parameter set");
	wpa_printf(MSG_DEBUG, "\tLatest Key AN....: %d", body->lan);
	wpa_printf(MSG_DEBUG, "\tLatest Key Tx....: %s", yes_no(body->ltx));
	wpa_printf(MSG_DEBUG, "\tLatest Key Rx....: %s", yes_no(body->lrx));
	wpa_printf(MSG_DEBUG, "\tOld Key AN.......: %d", body->oan);
	wpa_printf(MSG_DEBUG, "\tOld Key Tx.......: %s", yes_no(body->otx));
	wpa_printf(MSG_DEBUG, "\tOld Key Rx.......: %s", yes_no(body->orx));
	wpa_printf(MSG_DEBUG, "\tPlain Tx.........: %s", yes_no(body->ptx));
	wpa_printf(MSG_DEBUG, "\tPlain Rx.........: %s", yes_no(body->prx));
	wpa_printf(MSG_DEBUG, "\tDelay Protect....: %s",
		   yes_no(body->delay_protect));
	wpa_printf(MSG_DEBUG, "\tBody Length......: %d", body_len);
	if (!body_len)
		return;

	wpa_printf(MSG_DEBUG, "\tKey Server MI....: %s", mi_txt(body->lsrv_mi));
	wpa_printf(MSG_DEBUG, "\tKey Number.......: %u",
		   be_to_host32(body->lkn));
	wpa_printf(MSG_DEBUG, "\tLowest PN........: %u",
		   be_to_host32(body->llpn));
	wpa_printf(MSG_DEBUG, "\tOld Key Server MI: %s", mi_txt(body->osrv_mi));
	wpa_printf(MSG_DEBUG, "\tOld Key Number...: %u",
		   be_to_host32(body->okn));
	wpa_printf(MSG_DEBUG, "\tOld Lowest PN....: %u",
		   be_to_host32(body->olpn));
}