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
struct radius_session {scalar_t__ t_c_timestamp; int t_c_filtering; } ;
struct radius_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_ATTR_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  RADIUS_DEBUG (char*,...) ; 
 int RADIUS_VENDOR_ATTR_WFA_HS20_TIMESTAMP ; 
 scalar_t__ RADIUS_VENDOR_ID_WFA ; 
 scalar_t__ WPA_GET_BE32 (int*) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,int**,size_t*,int*) ; 

__attribute__((used)) static void radius_server_hs20_t_c_check(struct radius_session *sess,
					 struct radius_msg *msg)
{
#ifdef CONFIG_HS20
	u8 *buf, *pos, *end, type, sublen, *timestamp = NULL;
	size_t len;

	buf = NULL;
	for (;;) {
		if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_VENDOR_SPECIFIC,
					    &buf, &len, buf) < 0)
			break;
		if (len < 6)
			continue;
		pos = buf;
		end = buf + len;
		if (WPA_GET_BE32(pos) != RADIUS_VENDOR_ID_WFA)
			continue;
		pos += 4;

		type = *pos++;
		sublen = *pos++;
		if (sublen < 2)
			continue; /* invalid length */
		sublen -= 2; /* skip header */
		if (pos + sublen > end)
			continue; /* invalid WFA VSA */

		if (type == RADIUS_VENDOR_ATTR_WFA_HS20_TIMESTAMP && len >= 4) {
			timestamp = pos;
			break;
		}
	}

	if (!timestamp)
		return;
	RADIUS_DEBUG("HS20-Timestamp: %u", WPA_GET_BE32(timestamp));
	if (sess->t_c_timestamp != WPA_GET_BE32(timestamp)) {
		RADIUS_DEBUG("Last read T&C timestamp does not match HS20-Timestamp --> require filtering");
		sess->t_c_filtering = 1;
	}
#endif /* CONFIG_HS20 */
}