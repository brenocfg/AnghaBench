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
struct radius_msg {TYPE_1__* hdr; int /*<<< orphan*/  buf; } ;
struct radius_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * authenticator; } ;

/* Variables and functions */
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ radius_msg_verify_msg_auth (struct radius_msg*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

int radius_msg_verify(struct radius_msg *msg, const u8 *secret,
		      size_t secret_len, struct radius_msg *sent_msg, int auth)
{
	const u8 *addr[4];
	size_t len[4];
	u8 hash[MD5_MAC_LEN];

	if (sent_msg == NULL) {
		wpa_printf(MSG_INFO, "No matching Access-Request message found");
		return 1;
	}

	if (auth &&
	    radius_msg_verify_msg_auth(msg, secret, secret_len,
				       sent_msg->hdr->authenticator)) {
		return 1;
	}

	/* ResponseAuth = MD5(Code+ID+Length+RequestAuth+Attributes+Secret) */
	addr[0] = (u8 *) msg->hdr;
	len[0] = 1 + 1 + 2;
	addr[1] = sent_msg->hdr->authenticator;
	len[1] = MD5_MAC_LEN;
	addr[2] = wpabuf_head_u8(msg->buf) + sizeof(struct radius_hdr);
	len[2] = wpabuf_len(msg->buf) - sizeof(struct radius_hdr);
	addr[3] = secret;
	len[3] = secret_len;
	if (md5_vector(4, addr, len, hash) < 0 ||
	    os_memcmp_const(hash, msg->hdr->authenticator, MD5_MAC_LEN) != 0) {
		wpa_printf(MSG_INFO, "Response Authenticator invalid!");
		return 1;
	}

	return 0;
}