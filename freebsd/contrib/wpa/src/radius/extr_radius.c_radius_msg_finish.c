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
struct radius_attr_hdr {int dummy; } ;
struct TYPE_2__ {void* length; } ;

/* Variables and functions */
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
 int /*<<< orphan*/  hmac_md5 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct radius_attr_hdr* radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

int radius_msg_finish(struct radius_msg *msg, const u8 *secret,
		      size_t secret_len)
{
	if (secret) {
		u8 auth[MD5_MAC_LEN];
		struct radius_attr_hdr *attr;

		os_memset(auth, 0, MD5_MAC_LEN);
		attr = radius_msg_add_attr(msg,
					   RADIUS_ATTR_MESSAGE_AUTHENTICATOR,
					   auth, MD5_MAC_LEN);
		if (attr == NULL) {
			wpa_printf(MSG_WARNING, "RADIUS: Could not add "
				   "Message-Authenticator");
			return -1;
		}
		msg->hdr->length = host_to_be16(wpabuf_len(msg->buf));
		hmac_md5(secret, secret_len, wpabuf_head(msg->buf),
			 wpabuf_len(msg->buf), (u8 *) (attr + 1));
	} else
		msg->hdr->length = host_to_be16(wpabuf_len(msg->buf));

	if (wpabuf_len(msg->buf) > 0xffff) {
		wpa_printf(MSG_WARNING, "RADIUS: Too long message (%lu)",
			   (unsigned long) wpabuf_len(msg->buf));
		return -1;
	}
	return 0;
}