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
typedef  int wpa_eapol_variable ;
typedef  int /*<<< orphan*/  u8 ;
struct ibss_rsn_peer {int dummy; } ;
struct ibss_rsn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  WPA_EAPOL_authorized 128 
 struct ibss_rsn_peer* ibss_rsn_get_peer (struct ibss_rsn*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ibss_set_sta_authorized (struct ibss_rsn*,struct ibss_rsn_peer*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void auth_set_eapol(void *ctx, const u8 *addr,
				       wpa_eapol_variable var, int value)
{
	struct ibss_rsn *ibss_rsn = ctx;
	struct ibss_rsn_peer *peer = ibss_rsn_get_peer(ibss_rsn, addr);

	if (peer == NULL)
		return;

	switch (var) {
	case WPA_EAPOL_authorized:
		ibss_set_sta_authorized(ibss_rsn, peer, value);
		break;
	default:
		/* do not handle any other event */
		wpa_printf(MSG_DEBUG, "AUTH: eapol event not handled %d", var);
		break;
	}
}