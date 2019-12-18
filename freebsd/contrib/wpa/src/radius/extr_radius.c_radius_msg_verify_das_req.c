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
typedef  int /*<<< orphan*/  zero ;
struct radius_attr_hdr {scalar_t__ type; } ;
typedef  struct radius_attr_hdr u8 ;
struct radius_msg {size_t attr_used; TYPE_1__* hdr; int /*<<< orphan*/  buf; } ;
struct radius_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  orig_authenticator ;
struct TYPE_2__ {struct radius_attr_hdr* authenticator; } ;

/* Variables and functions */
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
 int /*<<< orphan*/  hmac_md5 (struct radius_attr_hdr const*,size_t,int /*<<< orphan*/ ,int,struct radius_attr_hdr*) ; 
 int /*<<< orphan*/  md5_vector (int,struct radius_attr_hdr const**,size_t*,struct radius_attr_hdr*) ; 
 scalar_t__ os_memcmp_const (struct radius_attr_hdr*,struct radius_attr_hdr*,int) ; 
 int /*<<< orphan*/  os_memcpy (struct radius_attr_hdr*,struct radius_attr_hdr*,int) ; 
 int /*<<< orphan*/  os_memset (struct radius_attr_hdr*,int /*<<< orphan*/ ,int) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

int radius_msg_verify_das_req(struct radius_msg *msg, const u8 *secret,
			      size_t secret_len,
			      int require_message_authenticator)
{
	const u8 *addr[4];
	size_t len[4];
	u8 zero[MD5_MAC_LEN];
	u8 hash[MD5_MAC_LEN];
	u8 auth[MD5_MAC_LEN], orig[MD5_MAC_LEN];
	u8 orig_authenticator[16];

	struct radius_attr_hdr *attr = NULL, *tmp;
	size_t i;

	os_memset(zero, 0, sizeof(zero));
	addr[0] = (u8 *) msg->hdr;
	len[0] = sizeof(struct radius_hdr) - MD5_MAC_LEN;
	addr[1] = zero;
	len[1] = MD5_MAC_LEN;
	addr[2] = (u8 *) (msg->hdr + 1);
	len[2] = wpabuf_len(msg->buf) - sizeof(struct radius_hdr);
	addr[3] = secret;
	len[3] = secret_len;
	md5_vector(4, addr, len, hash);
	if (os_memcmp_const(msg->hdr->authenticator, hash, MD5_MAC_LEN) != 0)
		return 1;

	for (i = 0; i < msg->attr_used; i++) {
		tmp = radius_get_attr_hdr(msg, i);
		if (tmp->type == RADIUS_ATTR_MESSAGE_AUTHENTICATOR) {
			if (attr != NULL) {
				wpa_printf(MSG_WARNING, "Multiple "
					   "Message-Authenticator attributes "
					   "in RADIUS message");
				return 1;
			}
			attr = tmp;
		}
	}

	if (attr == NULL) {
		if (require_message_authenticator) {
			wpa_printf(MSG_WARNING,
				   "Missing Message-Authenticator attribute in RADIUS message");
			return 1;
		}
		return 0;
	}

	os_memcpy(orig, attr + 1, MD5_MAC_LEN);
	os_memset(attr + 1, 0, MD5_MAC_LEN);
	os_memcpy(orig_authenticator, msg->hdr->authenticator,
		  sizeof(orig_authenticator));
	os_memset(msg->hdr->authenticator, 0,
		  sizeof(msg->hdr->authenticator));
	hmac_md5(secret, secret_len, wpabuf_head(msg->buf),
		 wpabuf_len(msg->buf), auth);
	os_memcpy(attr + 1, orig, MD5_MAC_LEN);
	os_memcpy(msg->hdr->authenticator, orig_authenticator,
		  sizeof(orig_authenticator));

	return os_memcmp_const(orig, auth, MD5_MAC_LEN) != 0;
}