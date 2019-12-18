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
struct radius_msg {int /*<<< orphan*/  buf; int /*<<< orphan*/  hdr; } ;
struct radius_attr_hdr {int length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 size_t RADIUS_MAX_ATTR_LEN ; 
 scalar_t__ TEST_FAIL () ; 
 scalar_t__ radius_msg_add_attr_to_array (struct radius_msg*,struct radius_attr_hdr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  wpabuf_mhead (int /*<<< orphan*/ ) ; 
 struct radius_attr_hdr* wpabuf_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,size_t) ; 
 size_t wpabuf_tailroom (int /*<<< orphan*/ ) ; 

struct radius_attr_hdr *radius_msg_add_attr(struct radius_msg *msg, u8 type,
					    const u8 *data, size_t data_len)
{
	size_t buf_needed;
	struct radius_attr_hdr *attr;

	if (TEST_FAIL())
		return NULL;

	if (data_len > RADIUS_MAX_ATTR_LEN) {
		wpa_printf(MSG_ERROR, "radius_msg_add_attr: too long attribute (%lu bytes)",
		       (unsigned long) data_len);
		return NULL;
	}

	buf_needed = sizeof(*attr) + data_len;

	if (wpabuf_tailroom(msg->buf) < buf_needed) {
		/* allocate more space for message buffer */
		if (wpabuf_resize(&msg->buf, buf_needed) < 0)
			return NULL;
		msg->hdr = wpabuf_mhead(msg->buf);
	}

	attr = wpabuf_put(msg->buf, sizeof(struct radius_attr_hdr));
	attr->type = type;
	attr->length = sizeof(*attr) + data_len;
	wpabuf_put_data(msg->buf, data, data_len);

	if (radius_msg_add_attr_to_array(msg, attr))
		return NULL;

	return attr;
}