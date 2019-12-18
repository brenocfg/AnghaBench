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
struct radius_msg {int /*<<< orphan*/  buf; TYPE_1__* hdr; } ;
struct radius_hdr {int dummy; } ;
struct radius_attr_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
 int /*<<< orphan*/  hmac_md5 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int /*<<< orphan*/  md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct radius_attr_hdr* radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

int radius_msg_finish_srv(struct radius_msg *msg, const u8 *secret,
			  size_t secret_len, const u8 *req_authenticator)
{
	u8 auth[MD5_MAC_LEN];
	struct radius_attr_hdr *attr;
	const u8 *addr[4];
	size_t len[4];

	os_memset(auth, 0, MD5_MAC_LEN);
	attr = radius_msg_add_attr(msg, RADIUS_ATTR_MESSAGE_AUTHENTICATOR,
				   auth, MD5_MAC_LEN);
	if (attr == NULL) {
		wpa_printf(MSG_ERROR, "WARNING: Could not add Message-Authenticator");
		return -1;
	}
	msg->hdr->length = host_to_be16(wpabuf_len(msg->buf));
	os_memcpy(msg->hdr->authenticator, req_authenticator,
		  sizeof(msg->hdr->authenticator));
	hmac_md5(secret, secret_len, wpabuf_head(msg->buf),
		 wpabuf_len(msg->buf), (u8 *) (attr + 1));

	/* ResponseAuth = MD5(Code+ID+Length+RequestAuth+Attributes+Secret) */
	addr[0] = (u8 *) msg->hdr;
	len[0] = 1 + 1 + 2;
	addr[1] = req_authenticator;
	len[1] = MD5_MAC_LEN;
	addr[2] = wpabuf_head_u8(msg->buf) + sizeof(struct radius_hdr);
	len[2] = wpabuf_len(msg->buf) - sizeof(struct radius_hdr);
	addr[3] = secret;
	len[3] = secret_len;
	md5_vector(4, addr, len, msg->hdr->authenticator);

	if (wpabuf_len(msg->buf) > 0xffff) {
		wpa_printf(MSG_WARNING, "RADIUS: Too long message (%lu)",
			   (unsigned long) wpabuf_len(msg->buf));
		return -1;
	}
	return 0;
}