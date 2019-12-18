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
struct ikev2_responder_data {int /*<<< orphan*/  state; int /*<<< orphan*/  keys; TYPE_1__ proposal; scalar_t__ IDr_len; } ;
struct ikev2_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKEV2_DONE ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_AUTHENTICATION ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_ENCRYPTED ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_IDr ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NO_NEXT_PAYLOAD ; 
 int /*<<< orphan*/  IKE_SA_AUTH ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ ikev2_build_auth (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_build_encrypted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikev2_build_hdr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ikev2_build_idr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * ikev2_build_sa_auth(struct ikev2_responder_data *data)
{
	struct wpabuf *msg, *plain;

	/* build IKE_SA_AUTH: HDR, SK {IDr, [CERT,] AUTH} */

	msg = wpabuf_alloc(sizeof(struct ikev2_hdr) + data->IDr_len + 1000);
	if (msg == NULL)
		return NULL;
	ikev2_build_hdr(data, msg, IKE_SA_AUTH, IKEV2_PAYLOAD_ENCRYPTED, 1);

	plain = wpabuf_alloc(data->IDr_len + 1000);
	if (plain == NULL) {
		wpabuf_free(msg);
		return NULL;
	}

	if (ikev2_build_idr(data, plain, IKEV2_PAYLOAD_AUTHENTICATION) ||
	    ikev2_build_auth(data, plain, IKEV2_PAYLOAD_NO_NEXT_PAYLOAD) ||
	    ikev2_build_encrypted(data->proposal.encr, data->proposal.integ,
				  &data->keys, 0, msg, plain,
				  IKEV2_PAYLOAD_IDr)) {
		wpabuf_free(plain);
		wpabuf_free(msg);
		return NULL;
	}
	wpabuf_free(plain);

	wpa_hexdump_buf(MSG_MSGDUMP, "IKEV2: Sending message (SA_AUTH)", msg);

	data->state = IKEV2_DONE;

	return msg;
}