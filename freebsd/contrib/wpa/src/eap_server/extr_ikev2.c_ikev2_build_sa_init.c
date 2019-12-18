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
struct wpabuf {int dummy; } ;
struct ikev2_initiator_data {struct wpabuf* i_sign_msg; int /*<<< orphan*/  i_nonce_len; int /*<<< orphan*/  i_nonce; int /*<<< orphan*/  i_spi; } ;
struct ikev2_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKEV2_NONCE_MIN_LEN ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_KEY_EXCHANGE ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NONCE ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NO_NEXT_PAYLOAD ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_SA ; 
 int /*<<< orphan*/  IKEV2_SPI_LEN ; 
 int /*<<< orphan*/  IKE_SA_INIT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  ikev2_build_hdr (struct ikev2_initiator_data*,struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_kei (struct ikev2_initiator_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_ni (struct ikev2_initiator_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_sai (struct ikev2_initiator_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikev2_update_hdr (struct wpabuf*) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct wpabuf* wpabuf_dup (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * ikev2_build_sa_init(struct ikev2_initiator_data *data)
{
	struct wpabuf *msg;

	/* build IKE_SA_INIT: HDR, SAi, KEi, Ni */

	if (os_get_random(data->i_spi, IKEV2_SPI_LEN))
		return NULL;
	wpa_hexdump(MSG_DEBUG, "IKEV2: IKE_SA Initiator's SPI",
		    data->i_spi, IKEV2_SPI_LEN);

	data->i_nonce_len = IKEV2_NONCE_MIN_LEN;
	if (random_get_bytes(data->i_nonce, data->i_nonce_len))
		return NULL;
	wpa_hexdump(MSG_DEBUG, "IKEV2: Ni", data->i_nonce, data->i_nonce_len);

	msg = wpabuf_alloc(sizeof(struct ikev2_hdr) + 1000);
	if (msg == NULL)
		return NULL;

	ikev2_build_hdr(data, msg, IKE_SA_INIT, IKEV2_PAYLOAD_SA, 0);
	if (ikev2_build_sai(data, msg, IKEV2_PAYLOAD_KEY_EXCHANGE) ||
	    ikev2_build_kei(data, msg, IKEV2_PAYLOAD_NONCE) ||
	    ikev2_build_ni(data, msg, IKEV2_PAYLOAD_NO_NEXT_PAYLOAD)) {
		wpabuf_free(msg);
		return NULL;
	}

	ikev2_update_hdr(msg);

	wpa_hexdump_buf(MSG_MSGDUMP, "IKEV2: Sending message (SA_INIT)", msg);

	wpabuf_free(data->i_sign_msg);
	data->i_sign_msg = wpabuf_dup(msg);

	return msg;
}