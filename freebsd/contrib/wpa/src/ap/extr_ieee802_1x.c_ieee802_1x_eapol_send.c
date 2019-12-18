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
struct sta_info {int flags; struct eapol_state_machine* eapol_sm; } ;
struct eapol_state_machine {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WLAN_STA_MAYBE_WPS ; 
 int WLAN_STA_WPS ; 
 int /*<<< orphan*/  WSC_ID_ENROLLEE ; 
 size_t WSC_ID_ENROLLEE_LEN ; 
 int /*<<< orphan*/  WSC_ID_REGISTRAR ; 
 size_t WSC_ID_REGISTRAR_LEN ; 
 int /*<<< orphan*/ * eap_get_identity (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  ieee802_1x_send (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ieee802_1x_eapol_send(void *ctx, void *sta_ctx, u8 type,
				  const u8 *data, size_t datalen)
{
#ifdef CONFIG_WPS
	struct sta_info *sta = sta_ctx;

	if ((sta->flags & (WLAN_STA_WPS | WLAN_STA_MAYBE_WPS)) ==
	    WLAN_STA_MAYBE_WPS) {
		const u8 *identity;
		size_t identity_len;
		struct eapol_state_machine *sm = sta->eapol_sm;

		identity = eap_get_identity(sm->eap, &identity_len);
		if (identity &&
		    ((identity_len == WSC_ID_ENROLLEE_LEN &&
		      os_memcmp(identity, WSC_ID_ENROLLEE,
				WSC_ID_ENROLLEE_LEN) == 0) ||
		     (identity_len == WSC_ID_REGISTRAR_LEN &&
		      os_memcmp(identity, WSC_ID_REGISTRAR,
				WSC_ID_REGISTRAR_LEN) == 0))) {
			wpa_printf(MSG_DEBUG, "WPS: WLAN_STA_MAYBE_WPS -> "
				   "WLAN_STA_WPS");
			sta->flags |= WLAN_STA_WPS;
		}
	}
#endif /* CONFIG_WPS */

	ieee802_1x_send(ctx, sta_ctx, type, data, datalen);
}