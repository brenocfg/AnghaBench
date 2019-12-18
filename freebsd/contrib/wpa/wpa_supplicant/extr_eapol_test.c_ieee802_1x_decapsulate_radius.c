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
struct wpabuf {int dummy; } ;
struct radius_msg {int dummy; } ;
struct ieee802_1x_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; int /*<<< orphan*/  version; } ;
struct eapol_test_data {TYPE_1__* wpa_s; struct wpabuf* last_eap_radius; int /*<<< orphan*/  ctrl_iface; struct radius_msg* last_recv_radius; } ;
struct eap_hdr {int code; int /*<<< orphan*/  length; int /*<<< orphan*/  identifier; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; int /*<<< orphan*/  eapol; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_VERSION ; 
#define  EAP_CODE_FAILURE 131 
#define  EAP_CODE_REQUEST 130 
#define  EAP_CODE_RESPONSE 129 
#define  EAP_CODE_SUCCESS 128 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAP_PACKET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* eap_type_text (int) ; 
 int /*<<< orphan*/  eapol_sm_rx_eapol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct ieee802_1x_hdr*) ; 
 struct ieee802_1x_hdr* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct eap_hdr*,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char*,int) ; 
 struct wpabuf* radius_msg_get_eap (struct radius_msg*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct eap_hdr* wpabuf_head (struct wpabuf*) ; 
 int* wpabuf_head_u8 (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void ieee802_1x_decapsulate_radius(struct eapol_test_data *e)
{
	struct wpabuf *eap;
	const struct eap_hdr *hdr;
	int eap_type = -1;
	char buf[64];
	struct radius_msg *msg;

	if (e->last_recv_radius == NULL)
		return;

	msg = e->last_recv_radius;

	eap = radius_msg_get_eap(msg);
	if (eap == NULL) {
		/* draft-aboba-radius-rfc2869bis-20.txt, Chap. 2.6.3:
		 * RADIUS server SHOULD NOT send Access-Reject/no EAP-Message
		 * attribute */
		wpa_printf(MSG_DEBUG, "could not extract "
			       "EAP-Message from RADIUS message");
		wpabuf_free(e->last_eap_radius);
		e->last_eap_radius = NULL;
		return;
	}

	if (wpabuf_len(eap) < sizeof(*hdr)) {
		wpa_printf(MSG_DEBUG, "too short EAP packet "
			       "received from authentication server");
		wpabuf_free(eap);
		return;
	}

	if (wpabuf_len(eap) > sizeof(*hdr))
		eap_type = (wpabuf_head_u8(eap))[sizeof(*hdr)];

	hdr = wpabuf_head(eap);
	switch (hdr->code) {
	case EAP_CODE_REQUEST:
		os_snprintf(buf, sizeof(buf), "EAP-Request-%s (%d)",
			    eap_type >= 0 ? eap_type_text(eap_type) : "??",
			    eap_type);
		break;
	case EAP_CODE_RESPONSE:
		os_snprintf(buf, sizeof(buf), "EAP Response-%s (%d)",
			    eap_type >= 0 ? eap_type_text(eap_type) : "??",
			    eap_type);
		break;
	case EAP_CODE_SUCCESS:
		os_strlcpy(buf, "EAP Success", sizeof(buf));
		/* LEAP uses EAP Success within an authentication, so must not
		 * stop here with eloop_terminate(); */
		break;
	case EAP_CODE_FAILURE:
		os_strlcpy(buf, "EAP Failure", sizeof(buf));
		if (e->ctrl_iface)
			break;
		eloop_terminate();
		break;
	default:
		os_strlcpy(buf, "unknown EAP code", sizeof(buf));
		wpa_hexdump_buf(MSG_DEBUG, "Decapsulated EAP packet", eap);
		break;
	}
	wpa_printf(MSG_DEBUG, "decapsulated EAP packet (code=%d "
		       "id=%d len=%d) from RADIUS server: %s",
		      hdr->code, hdr->identifier, ntohs(hdr->length), buf);

	/* sta->eapol_sm->be_auth.idFromServer = hdr->identifier; */

	wpabuf_free(e->last_eap_radius);
	e->last_eap_radius = eap;

	{
		struct ieee802_1x_hdr *dot1x;
		dot1x = os_malloc(sizeof(*dot1x) + wpabuf_len(eap));
		assert(dot1x != NULL);
		dot1x->version = EAPOL_VERSION;
		dot1x->type = IEEE802_1X_TYPE_EAP_PACKET;
		dot1x->length = htons(wpabuf_len(eap));
		os_memcpy((u8 *) (dot1x + 1), wpabuf_head(eap),
			  wpabuf_len(eap));
		eapol_sm_rx_eapol(e->wpa_s->eapol, e->wpa_s->bssid,
				  (u8 *) dot1x,
				  sizeof(*dot1x) + wpabuf_len(eap));
		os_free(dot1x);
	}
}