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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  tmp ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int /*<<< orphan*/  identifier; } ;
struct radius_das_data {int (* disconnect ) (int /*<<< orphan*/ ,struct radius_das_attrs*) ;int /*<<< orphan*/  ctx; } ;
struct radius_das_attrs {size_t nas_identifier_len; size_t user_name_len; size_t acct_session_id_len; size_t acct_multi_session_id_len; size_t cui_len; scalar_t__* cui; scalar_t__* acct_multi_session_id; scalar_t__* acct_session_id; scalar_t__* user_name; scalar_t__* sta_addr; scalar_t__* nas_identifier; scalar_t__* nas_ipv6_addr; scalar_t__* nas_ip_addr; } ;
typedef  enum radius_das_res { ____Placeholder_radius_das_res } radius_das_res ;
typedef  int /*<<< orphan*/  attrs ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ RADIUS_ATTR_ACCT_MULTI_SESSION_ID ; 
 scalar_t__ RADIUS_ATTR_ACCT_SESSION_ID ; 
 scalar_t__ RADIUS_ATTR_CALLING_STATION_ID ; 
 scalar_t__ RADIUS_ATTR_CHARGEABLE_USER_IDENTITY ; 
 int /*<<< orphan*/  RADIUS_ATTR_ERROR_CAUSE ; 
 scalar_t__ RADIUS_ATTR_EVENT_TIMESTAMP ; 
 scalar_t__ RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
 scalar_t__ RADIUS_ATTR_NAS_IDENTIFIER ; 
 scalar_t__ RADIUS_ATTR_NAS_IPV6_ADDRESS ; 
 scalar_t__ RADIUS_ATTR_NAS_IP_ADDRESS ; 
 scalar_t__ RADIUS_ATTR_USER_NAME ; 
 int /*<<< orphan*/  RADIUS_CODE_DISCONNECT_ACK ; 
 int /*<<< orphan*/  RADIUS_CODE_DISCONNECT_NAK ; 
#define  RADIUS_DAS_COA_FAILED 132 
#define  RADIUS_DAS_MULTI_SESSION_MATCH 131 
#define  RADIUS_DAS_NAS_MISMATCH 130 
#define  RADIUS_DAS_SESSION_NOT_FOUND 129 
#define  RADIUS_DAS_SUCCESS 128 
 scalar_t__ hwaddr_aton2 (char*,scalar_t__*) ; 
 int /*<<< orphan*/  os_memcpy (char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct radius_das_attrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ radius_msg_find_unlisted_attr (struct radius_msg*,scalar_t__*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,scalar_t__,scalar_t__**,size_t*,int /*<<< orphan*/ *) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct radius_das_attrs*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static struct radius_msg * radius_das_disconnect(struct radius_das_data *das,
						 struct radius_msg *msg,
						 const char *abuf,
						 int from_port)
{
	struct radius_hdr *hdr;
	struct radius_msg *reply;
	u8 allowed[] = {
		RADIUS_ATTR_USER_NAME,
		RADIUS_ATTR_NAS_IP_ADDRESS,
		RADIUS_ATTR_CALLING_STATION_ID,
		RADIUS_ATTR_NAS_IDENTIFIER,
		RADIUS_ATTR_ACCT_SESSION_ID,
		RADIUS_ATTR_ACCT_MULTI_SESSION_ID,
		RADIUS_ATTR_EVENT_TIMESTAMP,
		RADIUS_ATTR_MESSAGE_AUTHENTICATOR,
		RADIUS_ATTR_CHARGEABLE_USER_IDENTITY,
#ifdef CONFIG_IPV6
		RADIUS_ATTR_NAS_IPV6_ADDRESS,
#endif /* CONFIG_IPV6 */
		0
	};
	int error = 405;
	u8 attr;
	enum radius_das_res res;
	struct radius_das_attrs attrs;
	u8 *buf;
	size_t len;
	char tmp[100];
	u8 sta_addr[ETH_ALEN];

	hdr = radius_msg_get_hdr(msg);

	attr = radius_msg_find_unlisted_attr(msg, allowed);
	if (attr) {
		wpa_printf(MSG_INFO, "DAS: Unsupported attribute %u in "
			   "Disconnect-Request from %s:%d", attr,
			   abuf, from_port);
		error = 401;
		goto fail;
	}

	os_memset(&attrs, 0, sizeof(attrs));

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_NAS_IP_ADDRESS,
				    &buf, &len, NULL) == 0) {
		if (len != 4) {
			wpa_printf(MSG_INFO, "DAS: Invalid NAS-IP-Address from %s:%d",
				   abuf, from_port);
			error = 407;
			goto fail;
		}
		attrs.nas_ip_addr = buf;
	}

#ifdef CONFIG_IPV6
	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_NAS_IPV6_ADDRESS,
				    &buf, &len, NULL) == 0) {
		if (len != 16) {
			wpa_printf(MSG_INFO, "DAS: Invalid NAS-IPv6-Address from %s:%d",
				   abuf, from_port);
			error = 407;
			goto fail;
		}
		attrs.nas_ipv6_addr = buf;
	}
#endif /* CONFIG_IPV6 */

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_NAS_IDENTIFIER,
				    &buf, &len, NULL) == 0) {
		attrs.nas_identifier = buf;
		attrs.nas_identifier_len = len;
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_CALLING_STATION_ID,
				    &buf, &len, NULL) == 0) {
		if (len >= sizeof(tmp))
			len = sizeof(tmp) - 1;
		os_memcpy(tmp, buf, len);
		tmp[len] = '\0';
		if (hwaddr_aton2(tmp, sta_addr) < 0) {
			wpa_printf(MSG_INFO, "DAS: Invalid Calling-Station-Id "
				   "'%s' from %s:%d", tmp, abuf, from_port);
			error = 407;
			goto fail;
		}
		attrs.sta_addr = sta_addr;
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_USER_NAME,
				    &buf, &len, NULL) == 0) {
		attrs.user_name = buf;
		attrs.user_name_len = len;
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_ACCT_SESSION_ID,
				    &buf, &len, NULL) == 0) {
		attrs.acct_session_id = buf;
		attrs.acct_session_id_len = len;
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_ACCT_MULTI_SESSION_ID,
				    &buf, &len, NULL) == 0) {
		attrs.acct_multi_session_id = buf;
		attrs.acct_multi_session_id_len = len;
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_CHARGEABLE_USER_IDENTITY,
				    &buf, &len, NULL) == 0) {
		attrs.cui = buf;
		attrs.cui_len = len;
	}

	res = das->disconnect(das->ctx, &attrs);
	switch (res) {
	case RADIUS_DAS_NAS_MISMATCH:
		wpa_printf(MSG_INFO, "DAS: NAS mismatch from %s:%d",
			   abuf, from_port);
		error = 403;
		break;
	case RADIUS_DAS_SESSION_NOT_FOUND:
		wpa_printf(MSG_INFO, "DAS: Session not found for request from "
			   "%s:%d", abuf, from_port);
		error = 503;
		break;
	case RADIUS_DAS_MULTI_SESSION_MATCH:
		wpa_printf(MSG_INFO,
			   "DAS: Multiple sessions match for request from %s:%d",
			   abuf, from_port);
		error = 508;
		break;
	case RADIUS_DAS_COA_FAILED:
		/* not used with Disconnect-Request */
		error = 405;
		break;
	case RADIUS_DAS_SUCCESS:
		error = 0;
		break;
	}

fail:
	reply = radius_msg_new(error ? RADIUS_CODE_DISCONNECT_NAK :
			       RADIUS_CODE_DISCONNECT_ACK, hdr->identifier);
	if (reply == NULL)
		return NULL;

	if (error) {
		if (!radius_msg_add_attr_int32(reply, RADIUS_ATTR_ERROR_CAUSE,
					       error)) {
			radius_msg_free(reply);
			return NULL;
		}
	}

	return reply;
}