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
struct radius_msg {int /*<<< orphan*/ * buf; int /*<<< orphan*/  hdr; } ;
struct radius_hdr {int /*<<< orphan*/  length; } ;
struct radius_attr_hdr {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 struct radius_msg* os_zalloc (int) ; 
 scalar_t__ radius_msg_add_attr_to_array (struct radius_msg*,struct radius_attr_hdr*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_initialize (struct radius_msg*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 
 int wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_mhead (int /*<<< orphan*/ *) ; 
 unsigned char* wpabuf_mhead_u8 (int /*<<< orphan*/ *) ; 

struct radius_msg * radius_msg_parse(const u8 *data, size_t len)
{
	struct radius_msg *msg;
	struct radius_hdr *hdr;
	struct radius_attr_hdr *attr;
	size_t msg_len;
	unsigned char *pos, *end;

	if (data == NULL || len < sizeof(*hdr))
		return NULL;

	hdr = (struct radius_hdr *) data;

	msg_len = be_to_host16(hdr->length);
	if (msg_len < sizeof(*hdr) || msg_len > len) {
		wpa_printf(MSG_INFO, "RADIUS: Invalid message length");
		return NULL;
	}

	if (msg_len < len) {
		wpa_printf(MSG_DEBUG, "RADIUS: Ignored %lu extra bytes after "
			   "RADIUS message", (unsigned long) len - msg_len);
	}

	msg = os_zalloc(sizeof(*msg));
	if (msg == NULL)
		return NULL;

	msg->buf = wpabuf_alloc_copy(data, msg_len);
	if (msg->buf == NULL || radius_msg_initialize(msg)) {
		radius_msg_free(msg);
		return NULL;
	}
	msg->hdr = wpabuf_mhead(msg->buf);

	/* parse attributes */
	pos = wpabuf_mhead_u8(msg->buf) + sizeof(struct radius_hdr);
	end = wpabuf_mhead_u8(msg->buf) + wpabuf_len(msg->buf);
	while (pos < end) {
		if ((size_t) (end - pos) < sizeof(*attr))
			goto fail;

		attr = (struct radius_attr_hdr *) pos;

		if (attr->length > end - pos || attr->length < sizeof(*attr))
			goto fail;

		/* TODO: check that attr->length is suitable for attr->type */

		if (radius_msg_add_attr_to_array(msg, attr))
			goto fail;

		pos += attr->length;
	}

	return msg;

 fail:
	radius_msg_free(msg);
	return NULL;
}