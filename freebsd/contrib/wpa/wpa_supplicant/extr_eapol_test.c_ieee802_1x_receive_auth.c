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
struct radius_msg {int dummy; } ;
struct radius_hdr {int code; } ;
struct eapol_test_data {int radius_identifier; int radius_access_accept_received; int radius_access_reject_received; scalar_t__ eapol_test_num_reauths; int /*<<< orphan*/  ctrl_iface; struct radius_msg* last_recv_radius; } ;
typedef  int /*<<< orphan*/  RadiusRxResult ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RADIUS_ATTR_EAP_MESSAGE ; 
 int /*<<< orphan*/  RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
#define  RADIUS_CODE_ACCESS_ACCEPT 129 
 int RADIUS_CODE_ACCESS_CHALLENGE ; 
#define  RADIUS_CODE_ACCESS_REJECT 128 
 int /*<<< orphan*/  RADIUS_RX_QUEUED ; 
 int /*<<< orphan*/  RADIUS_RX_UNKNOWN ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  ieee802_1x_decapsulate_radius (struct eapol_test_data*) ; 
 int /*<<< orphan*/  ieee802_1x_get_keys (struct eapol_test_data*,struct radius_msg*,struct radius_msg*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_get_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 scalar_t__ radius_msg_verify (struct radius_msg*,int /*<<< orphan*/  const*,size_t,struct radius_msg*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static RadiusRxResult
ieee802_1x_receive_auth(struct radius_msg *msg, struct radius_msg *req,
			const u8 *shared_secret, size_t shared_secret_len,
			void *data)
{
	struct eapol_test_data *e = data;
	struct radius_hdr *hdr = radius_msg_get_hdr(msg);

	/* RFC 2869, Ch. 5.13: valid Message-Authenticator attribute MUST be
	 * present when packet contains an EAP-Message attribute */
	if (hdr->code == RADIUS_CODE_ACCESS_REJECT &&
	    radius_msg_get_attr(msg, RADIUS_ATTR_MESSAGE_AUTHENTICATOR, NULL,
				0) < 0 &&
	    radius_msg_get_attr(msg, RADIUS_ATTR_EAP_MESSAGE, NULL, 0) < 0) {
		wpa_printf(MSG_DEBUG, "Allowing RADIUS "
			      "Access-Reject without Message-Authenticator "
			      "since it does not include EAP-Message\n");
	} else if (radius_msg_verify(msg, shared_secret, shared_secret_len,
				     req, 1)) {
		printf("Incoming RADIUS packet did not have correct "
		       "Message-Authenticator - dropped\n");
		return RADIUS_RX_UNKNOWN;
	}

	if (hdr->code != RADIUS_CODE_ACCESS_ACCEPT &&
	    hdr->code != RADIUS_CODE_ACCESS_REJECT &&
	    hdr->code != RADIUS_CODE_ACCESS_CHALLENGE) {
		printf("Unknown RADIUS message code\n");
		return RADIUS_RX_UNKNOWN;
	}

	e->radius_identifier = -1;
	wpa_printf(MSG_DEBUG, "RADIUS packet matching with station");

	radius_msg_free(e->last_recv_radius);
	e->last_recv_radius = msg;

	switch (hdr->code) {
	case RADIUS_CODE_ACCESS_ACCEPT:
		e->radius_access_accept_received = 1;
		ieee802_1x_get_keys(e, msg, req, shared_secret,
				    shared_secret_len);
		break;
	case RADIUS_CODE_ACCESS_REJECT:
		e->radius_access_reject_received = 1;
		break;
	}

	ieee802_1x_decapsulate_radius(e);

	if ((hdr->code == RADIUS_CODE_ACCESS_ACCEPT &&
	     e->eapol_test_num_reauths < 0) ||
	    hdr->code == RADIUS_CODE_ACCESS_REJECT) {
		if (!e->ctrl_iface)
			eloop_terminate();
	}

	return RADIUS_RX_QUEUED;
}