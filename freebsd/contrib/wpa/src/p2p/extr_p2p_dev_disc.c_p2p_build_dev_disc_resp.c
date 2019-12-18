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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_DEV_DISC_RESP ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_public_action_hdr (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_status (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc (int) ; 

__attribute__((used)) static struct wpabuf * p2p_build_dev_disc_resp(u8 dialog_token, u8 status)
{
	struct wpabuf *buf;
	u8 *len;

	buf = wpabuf_alloc(100);
	if (buf == NULL)
		return NULL;

	p2p_buf_add_public_action_hdr(buf, P2P_DEV_DISC_RESP, dialog_token);

	len = p2p_buf_add_ie_hdr(buf);
	p2p_buf_add_status(buf, status);
	p2p_buf_update_ie_hdr(buf, len);

	return buf;
}