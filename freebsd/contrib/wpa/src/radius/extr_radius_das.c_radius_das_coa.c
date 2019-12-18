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
typedef  int /*<<< orphan*/  tmp ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int /*<<< orphan*/  identifier; } ;
struct radius_das_data {int (* coa ) (int /*<<< orphan*/ ,struct radius_das_attrs*) ;int /*<<< orphan*/  ctx; } ;
struct radius_das_attrs {int* nas_ip_addr; int* nas_ipv6_addr; int* nas_identifier; size_t nas_identifier_len; int* sta_addr; int* user_name; size_t user_name_len; int* acct_session_id; size_t acct_session_id_len; int* acct_multi_session_id; size_t acct_multi_session_id_len; int* cui; size_t cui_len; int* hs20_t_c_filtering; } ;
typedef  enum radius_das_res { ____Placeholder_radius_das_res } radius_das_res ;
typedef  int /*<<< orphan*/  attrs ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int RADIUS_ATTR_ACCT_MULTI_SESSION_ID ; 
 int RADIUS_ATTR_ACCT_SESSION_ID ; 
 int RADIUS_ATTR_CALLING_STATION_ID ; 
 int RADIUS_ATTR_CHARGEABLE_USER_IDENTITY ; 
 int /*<<< orphan*/  RADIUS_ATTR_ERROR_CAUSE ; 
 int RADIUS_ATTR_EVENT_TIMESTAMP ; 
 int RADIUS_ATTR_MESSAGE_AUTHENTICATOR ; 
 int RADIUS_ATTR_NAS_IDENTIFIER ; 
 int RADIUS_ATTR_NAS_IPV6_ADDRESS ; 
 int RADIUS_ATTR_NAS_IP_ADDRESS ; 
 int RADIUS_ATTR_USER_NAME ; 
 int RADIUS_ATTR_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  RADIUS_CODE_COA_ACK ; 
 int /*<<< orphan*/  RADIUS_CODE_COA_NAK ; 
#define  RADIUS_DAS_COA_FAILED 132 
#define  RADIUS_DAS_MULTI_SESSION_MATCH 131 
#define  RADIUS_DAS_NAS_MISMATCH 130 
#define  RADIUS_DAS_SESSION_NOT_FOUND 129 
#define  RADIUS_DAS_SUCCESS 128 
 int RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING ; 
 scalar_t__ RADIUS_VENDOR_ID_WFA ; 
 scalar_t__ WPA_GET_BE32 (int*) ; 
 scalar_t__ hwaddr_aton2 (char*,int*) ; 
 int /*<<< orphan*/  os_memcpy (char*,int*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct radius_das_attrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int) ; 
 int radius_msg_find_unlisted_attr (struct radius_msg*,int*) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int,int**,size_t*,int /*<<< orphan*/ *) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct radius_das_attrs*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct radius_msg * radius_das_coa(struct radius_das_data *das,
					  struct radius_msg *msg,
					  const char *abuf, int from_port)
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
#ifdef CONFIG_HS20
		RADIUS_ATTR_VENDOR_SPECIFIC,
#endif /* CONFIG_HS20 */
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

	if (!das->coa) {
		wpa_printf(MSG_INFO, "DAS: CoA not supported");
		goto fail;
	}

	attr = radius_msg_find_unlisted_attr(msg, allowed);
	if (attr) {
		wpa_printf(MSG_INFO,
			   "DAS: Unsupported attribute %u in CoA-Request from %s:%d",
			   attr, abuf, from_port);
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

#ifdef CONFIG_HS20
	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_VENDOR_SPECIFIC,
				    &buf, &len, NULL) == 0) {
		if (len < 10 || WPA_GET_BE32(buf) != RADIUS_VENDOR_ID_WFA ||
		    buf[4] != RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING ||
		    buf[5] < 6) {
			wpa_printf(MSG_INFO,
				   "DAS: Unsupported attribute %u in CoA-Request from %s:%d",
				   attr, abuf, from_port);
			error = 401;
			goto fail;
		}
		attrs.hs20_t_c_filtering = &buf[6];
	}

	if (!attrs.hs20_t_c_filtering) {
			wpa_printf(MSG_INFO,
				   "DAS: No supported authorization change attribute in CoA-Request from %s:%d",
				   abuf, from_port);
			error = 402;
			goto fail;
	}
#endif /* CONFIG_HS20 */

	res = das->coa(das->ctx, &attrs);
	switch (res) {
	case RADIUS_DAS_NAS_MISMATCH:
		wpa_printf(MSG_INFO, "DAS: NAS mismatch from %s:%d",
			   abuf, from_port);
		error = 403;
		break;
	case RADIUS_DAS_SESSION_NOT_FOUND:
		wpa_printf(MSG_INFO,
			   "DAS: Session not found for request from %s:%d",
			   abuf, from_port);
		error = 503;
		break;
	case RADIUS_DAS_MULTI_SESSION_MATCH:
		wpa_printf(MSG_INFO,
			   "DAS: Multiple sessions match for request from %s:%d",
			   abuf, from_port);
		error = 508;
		break;
	case RADIUS_DAS_COA_FAILED:
		wpa_printf(MSG_INFO, "DAS: CoA failed for request from %s:%d",
			   abuf, from_port);
		error = 407;
		break;
	case RADIUS_DAS_SUCCESS:
		error = 0;
		break;
	}

fail:
	reply = radius_msg_new(error ? RADIUS_CODE_COA_NAK :
			       RADIUS_CODE_COA_ACK, hdr->identifier);
	if (!reply)
		return NULL;

	if (error &&
	    !radius_msg_add_attr_int32(reply, RADIUS_ATTR_ERROR_CAUSE, error)) {
		radius_msg_free(reply);
		return NULL;
	}

	return reply;
}