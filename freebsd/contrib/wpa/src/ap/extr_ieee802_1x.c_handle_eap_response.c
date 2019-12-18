#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {struct eapol_state_machine* eapol_sm; } ;
struct hostapd_data {int dummy; } ;
struct eapol_state_machine {int /*<<< orphan*/  eapolEap; TYPE_1__* eap_if; int /*<<< orphan*/  dot1xAuthEapolRespFramesRx; int /*<<< orphan*/  addr; int /*<<< orphan*/  eap_type_supp; } ;
struct eap_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  identifier; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {int /*<<< orphan*/  eapRespData; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE8021X ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_server_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (struct eap_hdr*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_eap_response(struct hostapd_data *hapd,
				struct sta_info *sta, struct eap_hdr *eap,
				size_t len)
{
	u8 type, *data;
	struct eapol_state_machine *sm = sta->eapol_sm;
	if (sm == NULL)
		return;

	data = (u8 *) (eap + 1);

	if (len < sizeof(*eap) + 1) {
		wpa_printf(MSG_INFO, "handle_eap_response: too short response data");
		return;
	}

	sm->eap_type_supp = type = data[0];

	hostapd_logger(hapd, sm->addr, HOSTAPD_MODULE_IEEE8021X,
		       HOSTAPD_LEVEL_DEBUG, "received EAP packet (code=%d "
		       "id=%d len=%d) from STA: EAP Response-%s (%d)",
		       eap->code, eap->identifier, be_to_host16(eap->length),
		       eap_server_get_name(0, type), type);

	sm->dot1xAuthEapolRespFramesRx++;

	wpabuf_free(sm->eap_if->eapRespData);
	sm->eap_if->eapRespData = wpabuf_alloc_copy(eap, len);
	sm->eapolEap = TRUE;
}