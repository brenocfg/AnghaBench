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
typedef  int u8 ;
struct eap_sim_msg {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 
 int* wpabuf_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,int) ; 

u8 * eap_sim_msg_add_full(struct eap_sim_msg *msg, u8 attr,
			  const u8 *data, size_t len)
{
	int attr_len = 2 + len;
	int pad_len;
	u8 *start;

	if (msg == NULL)
		return NULL;

	pad_len = (4 - attr_len % 4) % 4;
	attr_len += pad_len;
	if (wpabuf_resize(&msg->buf, attr_len))
		return NULL;
	start = wpabuf_put(msg->buf, 0);
	wpabuf_put_u8(msg->buf, attr);
	wpabuf_put_u8(msg->buf, attr_len / 4);
	wpabuf_put_data(msg->buf, data, len);
	if (pad_len)
		os_memset(wpabuf_put(msg->buf, pad_len), 0, pad_len);
	return start;
}