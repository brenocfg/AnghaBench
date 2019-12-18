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
struct ikev2_responder_data {scalar_t__ last_msg; int /*<<< orphan*/  state; int /*<<< orphan*/  keys; TYPE_1__ proposal; } ;
struct ikev2_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKEV2_FAILED ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_ENCRYPTED ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NOTIFICATION ; 
 int /*<<< orphan*/  IKEV2_PAYLOAD_NO_NEXT_PAYLOAD ; 
 int /*<<< orphan*/  IKE_SA_AUTH ; 
 int /*<<< orphan*/  IKE_SA_INIT ; 
 scalar_t__ LAST_MSG_SA_AUTH ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  SA_INIT ; 
 scalar_t__ ikev2_build_encrypted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikev2_build_hdr (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ikev2_build_notification (struct ikev2_responder_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikev2_update_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * ikev2_build_notify(struct ikev2_responder_data *data)
{
	struct wpabuf *msg;

	msg = wpabuf_alloc(sizeof(struct ikev2_hdr) + 1000);
	if (msg == NULL)
		return NULL;
	if (data->last_msg == LAST_MSG_SA_AUTH) {
		/* HDR, SK{N} */
		struct wpabuf *plain = wpabuf_alloc(100);
		if (plain == NULL) {
			wpabuf_free(msg);
			return NULL;
		}
		ikev2_build_hdr(data, msg, IKE_SA_AUTH,
				IKEV2_PAYLOAD_ENCRYPTED, 1);
		if (ikev2_build_notification(data, plain,
					     IKEV2_PAYLOAD_NO_NEXT_PAYLOAD) ||
		    ikev2_build_encrypted(data->proposal.encr,
					  data->proposal.integ,
					  &data->keys, 0, msg, plain,
					  IKEV2_PAYLOAD_NOTIFICATION)) {
			wpabuf_free(plain);
			wpabuf_free(msg);
			return NULL;
		}
		wpabuf_free(plain);
		data->state = IKEV2_FAILED;
	} else {
		/* HDR, N */
		ikev2_build_hdr(data, msg, IKE_SA_INIT,
				IKEV2_PAYLOAD_NOTIFICATION, 0);
		if (ikev2_build_notification(data, msg,
					     IKEV2_PAYLOAD_NO_NEXT_PAYLOAD)) {
			wpabuf_free(msg);
			return NULL;
		}
		data->state = SA_INIT;
	}

	ikev2_update_hdr(msg);

	wpa_hexdump_buf(MSG_MSGDUMP, "IKEV2: Sending message (Notification)",
			msg);

	return msg;
}