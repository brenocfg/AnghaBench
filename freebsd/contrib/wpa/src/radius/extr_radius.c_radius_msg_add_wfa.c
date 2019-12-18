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
struct radius_msg {int dummy; } ;
struct radius_attr_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_ATTR_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  RADIUS_VENDOR_ID_WFA ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 struct radius_attr_hdr* radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int radius_msg_add_wfa(struct radius_msg *msg, u8 subtype, const u8 *data,
		       size_t len)
{
	struct radius_attr_hdr *attr;
	u8 *buf, *pos;
	size_t alen;

	alen = 4 + 2 + len;
	buf = os_malloc(alen);
	if (buf == NULL)
		return 0;
	pos = buf;
	WPA_PUT_BE32(pos, RADIUS_VENDOR_ID_WFA);
	pos += 4;
	*pos++ = subtype;
	*pos++ = 2 + len;
	os_memcpy(pos, data, len);
	attr = radius_msg_add_attr(msg, RADIUS_ATTR_VENDOR_SPECIFIC,
				   buf, alen);
	os_free(buf);
	if (attr == NULL)
		return 0;

	return 1;
}