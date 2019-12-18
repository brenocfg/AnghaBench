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
struct wpabuf {int dummy; } ;
struct sta_info {char* identity; char* radius_cui; scalar_t__ ipaddr; int /*<<< orphan*/  eapol_sm; int /*<<< orphan*/  addr; } ;
struct radius_msg {int dummy; } ;
struct os_time {int sec; } ;
struct hostapd_data {TYPE_1__* conf; int /*<<< orphan*/  radius; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  radius_acct_req_attr; scalar_t__ ieee802_1x; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int RADIUS_ACCT_AUTHENTIC_LOCAL ; 
 int RADIUS_ACCT_AUTHENTIC_RADIUS ; 
 int /*<<< orphan*/  RADIUS_ADDR_FORMAT ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_AUTHENTIC ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_DELAY_TIME ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_STATUS_TYPE ; 
 int /*<<< orphan*/  RADIUS_ATTR_CHARGEABLE_USER_IDENTITY ; 
 int /*<<< orphan*/  RADIUS_ATTR_CLASS ; 
 int /*<<< orphan*/  RADIUS_ATTR_EVENT_TIMESTAMP ; 
 int /*<<< orphan*/  RADIUS_ATTR_FRAMED_IP_ADDRESS ; 
 int /*<<< orphan*/  RADIUS_ATTR_USER_NAME ; 
 int /*<<< orphan*/  RADIUS_CODE_ACCOUNTING_REQUEST ; 
 scalar_t__ add_common_radius_attr (struct hostapd_data*,int /*<<< orphan*/ ,struct sta_info*,struct radius_msg*) ; 
 scalar_t__ add_sqlite_radius_attr (struct hostapd_data*,struct sta_info*,struct radius_msg*,int) ; 
 int be_to_host32 (scalar_t__) ; 
 int /*<<< orphan*/  hostapd_config_get_radius_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee802_1x_get_identity (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * ieee802_1x_get_radius_class (int /*<<< orphan*/ ,size_t*,int) ; 
 struct wpabuf* ieee802_1x_get_radius_cui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t os_strlen (char*) ; 
 int /*<<< orphan*/  radius_client_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static struct radius_msg * accounting_msg(struct hostapd_data *hapd,
					  struct sta_info *sta,
					  int status_type)
{
	struct radius_msg *msg;
	char buf[128];
	u8 *val;
	size_t len;
	int i;
	struct wpabuf *b;
	struct os_time now;

	msg = radius_msg_new(RADIUS_CODE_ACCOUNTING_REQUEST,
			     radius_client_get_id(hapd->radius));
	if (msg == NULL) {
		wpa_printf(MSG_INFO, "Could not create new RADIUS packet");
		return NULL;
	}

	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_ACCT_STATUS_TYPE,
				       status_type)) {
		wpa_printf(MSG_INFO, "Could not add Acct-Status-Type");
		goto fail;
	}

	if (sta) {
		if (!hostapd_config_get_radius_attr(
			    hapd->conf->radius_acct_req_attr,
			    RADIUS_ATTR_ACCT_AUTHENTIC) &&
		    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_ACCT_AUTHENTIC,
					       hapd->conf->ieee802_1x ?
					       RADIUS_ACCT_AUTHENTIC_RADIUS :
					       RADIUS_ACCT_AUTHENTIC_LOCAL)) {
			wpa_printf(MSG_INFO, "Could not add Acct-Authentic");
			goto fail;
		}

		/* Use 802.1X identity if available */
		val = ieee802_1x_get_identity(sta->eapol_sm, &len);

		/* Use RADIUS ACL identity if 802.1X provides no identity */
		if (!val && sta->identity) {
			val = (u8 *) sta->identity;
			len = os_strlen(sta->identity);
		}

		/* Use STA MAC if neither 802.1X nor RADIUS ACL provided
		 * identity */
		if (!val) {
			os_snprintf(buf, sizeof(buf), RADIUS_ADDR_FORMAT,
				    MAC2STR(sta->addr));
			val = (u8 *) buf;
			len = os_strlen(buf);
		}

		if (!radius_msg_add_attr(msg, RADIUS_ATTR_USER_NAME, val,
					 len)) {
			wpa_printf(MSG_INFO, "Could not add User-Name");
			goto fail;
		}
	}

	if (add_common_radius_attr(hapd, hapd->conf->radius_acct_req_attr, sta,
				   msg) < 0)
		goto fail;

	if (sta && add_sqlite_radius_attr(hapd, sta, msg, 1) < 0)
		goto fail;

	if (sta) {
		for (i = 0; ; i++) {
			val = ieee802_1x_get_radius_class(sta->eapol_sm, &len,
							  i);
			if (val == NULL)
				break;

			if (!radius_msg_add_attr(msg, RADIUS_ATTR_CLASS,
						 val, len)) {
				wpa_printf(MSG_INFO, "Could not add Class");
				goto fail;
			}
		}

		b = ieee802_1x_get_radius_cui(sta->eapol_sm);
		if (b &&
		    !radius_msg_add_attr(msg,
					 RADIUS_ATTR_CHARGEABLE_USER_IDENTITY,
					 wpabuf_head(b), wpabuf_len(b))) {
			wpa_printf(MSG_ERROR, "Could not add CUI");
			goto fail;
		}

		if (!b && sta->radius_cui &&
		    !radius_msg_add_attr(msg,
					 RADIUS_ATTR_CHARGEABLE_USER_IDENTITY,
					 (u8 *) sta->radius_cui,
					 os_strlen(sta->radius_cui))) {
			wpa_printf(MSG_ERROR, "Could not add CUI from ACL");
			goto fail;
		}

		if (sta->ipaddr &&
		    !radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_FRAMED_IP_ADDRESS,
					       be_to_host32(sta->ipaddr))) {
			wpa_printf(MSG_ERROR,
				   "Could not add Framed-IP-Address");
			goto fail;
		}
	}

	os_get_time(&now);
	if (now.sec > 1000000000 &&
	    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_EVENT_TIMESTAMP,
				       now.sec)) {
		wpa_printf(MSG_INFO, "Could not add Event-Timestamp");
		goto fail;
	}

	/*
	 * Add Acct-Delay-Time with zero value for the first transmission. This
	 * will be updated within radius_client.c when retransmitting the frame.
	 */
	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_ACCT_DELAY_TIME, 0)) {
		wpa_printf(MSG_INFO, "Could not add Acct-Delay-Time");
		goto fail;
	}

	return msg;

 fail:
	radius_msg_free(msg);
	return NULL;
}