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
struct TYPE_2__ {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int /*<<< orphan*/  md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

void radius_msg_finish_acct_resp(struct radius_msg *msg, const u8 *secret,
				 size_t secret_len, const u8 *req_authenticator)
{
	const u8 *addr[2];
	size_t len[2];

	msg->hdr->length = host_to_be16(wpabuf_len(msg->buf));
	os_memcpy(msg->hdr->authenticator, req_authenticator, MD5_MAC_LEN);
	addr[0] = wpabuf_head(msg->buf);
	len[0] = wpabuf_len(msg->buf);
	addr[1] = secret;
	len[1] = secret_len;
	md5_vector(2, addr, len, msg->hdr->authenticator);

	if (wpabuf_len(msg->buf) > 0xffff) {
		wpa_printf(MSG_WARNING, "RADIUS: Too long messages (%lu)",
			   (unsigned long) wpabuf_len(msg->buf));
	}
}