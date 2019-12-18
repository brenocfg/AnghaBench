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
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  integ; int /*<<< orphan*/  encr; } ;
struct ikev2_responder_data {scalar_t__ peer_auth; struct wpabuf* r_sign_msg; int /*<<< orphan*/  state; int /*<<< orphan*/  keys; TYPE_1__ proposal; scalar_t__ IDr_len; int /*<<< orphan*/  r_nonce_len; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  r_spi; } ;
struct ikev2_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKEV2_NONCE_MIN_LEN ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_ENCRYPTED ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_IDr ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_KEY_EXCHANGE ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NONCE ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NO_NEXT_PAYLOAD ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_SA ; 
 int /*<<< orphan*/  IKEV2_SPI_LEN ; 
 int /*<<< orphan*/  IKE_SA_INIT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ PEER_AUTH_CERT ; 
 scalar_t__ PEER_AUTH_SECRET ; 
 int /*<<< orphan*/  SA_AUTH ; 
 scalar_t__ ikev2_build_encrypted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikev2_build_hdr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_idr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_ker (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_nr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_sar1 (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_derive_keys (struct ikev2_responder_data*) ; 
 int /*<<< orphan*/  ikev2_update_hdr (struct wpabuf*) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 struct wpabuf* wpabuf_dup (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * ikev2_build_sa_init(struct ikev2_responder_data *data)
{
	struct wpabuf *msg;

	/* build IKE_SA_INIT: HDR, SAr1, KEr, Nr, [CERTREQ], [SK{IDr}] */

	if (os_get_random(data->r_spi, IKEV2_SPI_LEN))
		return NULL;
	wpa_hexdump(MSG_DEBUG, "IKEV2: IKE_SA Responder's SPI",
		    data->r_spi, IKEV2_SPI_LEN);

	data->r_nonce_len = IKEV2_NONCE_MIN_LEN;
	if (random_get_bytes(data->r_nonce, data->r_nonce_len))
		return NULL;
	wpa_hexdump(MSG_DEBUG, "IKEV2: Nr", data->r_nonce, data->r_nonce_len);

	msg = wpabuf_alloc(sizeof(struct ikev2_hdr) + data->IDr_len + 1500);
	if (msg == NULL)
		return NULL;

	ikev2_build_hdr(data, msg, IKE_SA_INIT, IKEV2_PAYLOAD_SA, 0);
	if (ikev2_build_sar1(data, msg, IKEV2_PAYLOAD_KEY_EXCHANGE) ||
	    ikev2_build_ker(data, msg, IKEV2_PAYLOAD_NONCE) ||
	    ikev2_build_nr(data, msg, data->peer_auth == PEER_AUTH_SECRET ?
			   IKEV2_PAYLOAD_ENCRYPTED :
			   IKEV2_PAYLOAD_NO_NEXT_PAYLOAD)) {
		wpabuf_free(msg);
		return NULL;
	}

	if (ikev2_derive_keys(data)) {
		wpabuf_free(msg);
		return NULL;
	}

	if (data->peer_auth == PEER_AUTH_CERT) {
		/* TODO: CERTREQ with SHA-1 hashes of Subject Public Key Info
		 * for trust agents */
	}

	if (data->peer_auth == PEER_AUTH_SECRET) {
		struct wpabuf *plain = wpabuf_alloc(data->IDr_len + 1000);
		if (plain == NULL) {
			wpabuf_free(msg);
			return NULL;
		}
		if (ikev2_build_idr(data, plain,
				    IKEV2_PAYLOAD_NO_NEXT_PAYLOAD) ||
		    ikev2_build_encrypted(data->proposal.encr,
					  data->proposal.integ,
					  &data->keys, 0, msg, plain,
					  IKEV2_PAYLOAD_IDr)) {
			wpabuf_free(plain);
			wpabuf_free(msg);
			return NULL;
		}
		wpabuf_free(plain);
	}

	ikev2_update_hdr(msg);

	wpa_hexdump_buf(MSG_MSGDUMP, "IKEV2: Sending message (SA_INIT)", msg);

	data->state = SA_AUTH;

	wpabuf_free(data->r_sign_msg);
	data->r_sign_msg = wpabuf_dup(msg);

	return msg;
}