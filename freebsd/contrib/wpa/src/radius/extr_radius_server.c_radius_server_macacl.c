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
typedef  int /*<<< orphan*/  tmp ;
struct radius_session {struct hostapd_radius_attr* accept_attr; scalar_t__ username; } ;
struct radius_server_data {int (* get_eap_user ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eap_user*) ;int /*<<< orphan*/  conf_ctx; } ;
struct radius_msg {int dummy; } ;
struct radius_hdr {int /*<<< orphan*/  authenticator; int /*<<< orphan*/  identifier; } ;
struct radius_client {int /*<<< orphan*/  shared_secret_len; scalar_t__ shared_secret; } ;
struct hostapd_radius_attr {int /*<<< orphan*/  val; int /*<<< orphan*/  type; struct hostapd_radius_attr* next; } ;
struct eap_user {int /*<<< orphan*/  password_len; int /*<<< orphan*/ * password; int /*<<< orphan*/  macacl; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  RADIUS_ATTR_PROXY_STATE ; 
 int /*<<< orphan*/  RADIUS_ATTR_USER_PASSWORD ; 
 int RADIUS_CODE_ACCESS_ACCEPT ; 
 int RADIUS_CODE_ACCESS_REJECT ; 
 int /*<<< orphan*/  RADIUS_DEBUG (char*) ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (struct eap_user*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ radius_msg_copy_attr (struct radius_msg*,struct radius_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ radius_msg_finish_srv (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 struct radius_hdr* radius_msg_get_hdr (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int,int /*<<< orphan*/ ) ; 
 int radius_user_password_hide (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eap_user*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct radius_msg *
radius_server_macacl(struct radius_server_data *data,
		     struct radius_client *client,
		     struct radius_session *sess,
		     struct radius_msg *request)
{
	struct radius_msg *msg;
	int code;
	struct radius_hdr *hdr = radius_msg_get_hdr(request);
	u8 *pw;
	size_t pw_len;

	code = RADIUS_CODE_ACCESS_ACCEPT;

	if (radius_msg_get_attr_ptr(request, RADIUS_ATTR_USER_PASSWORD, &pw,
				    &pw_len, NULL) < 0) {
		RADIUS_DEBUG("Could not get User-Password");
		code = RADIUS_CODE_ACCESS_REJECT;
	} else {
		int res;
		struct eap_user tmp;

		os_memset(&tmp, 0, sizeof(tmp));
		res = data->get_eap_user(data->conf_ctx, (u8 *) sess->username,
					 os_strlen(sess->username), 0, &tmp);
		if (res || !tmp.macacl || tmp.password == NULL) {
			RADIUS_DEBUG("No MAC ACL user entry");
			bin_clear_free(tmp.password, tmp.password_len);
			code = RADIUS_CODE_ACCESS_REJECT;
		} else {
			u8 buf[128];
			res = radius_user_password_hide(
				request, tmp.password, tmp.password_len,
				(u8 *) client->shared_secret,
				client->shared_secret_len,
				buf, sizeof(buf));
			bin_clear_free(tmp.password, tmp.password_len);

			if (res < 0 || pw_len != (size_t) res ||
			    os_memcmp_const(pw, buf, res) != 0) {
				RADIUS_DEBUG("Incorrect User-Password");
				code = RADIUS_CODE_ACCESS_REJECT;
			}
		}
	}

	msg = radius_msg_new(code, hdr->identifier);
	if (msg == NULL) {
		RADIUS_DEBUG("Failed to allocate reply message");
		return NULL;
	}

	if (radius_msg_copy_attr(msg, request, RADIUS_ATTR_PROXY_STATE) < 0) {
		RADIUS_DEBUG("Failed to copy Proxy-State attribute(s)");
		radius_msg_free(msg);
		return NULL;
	}

	if (code == RADIUS_CODE_ACCESS_ACCEPT) {
		struct hostapd_radius_attr *attr;
		for (attr = sess->accept_attr; attr; attr = attr->next) {
			if (!radius_msg_add_attr(msg, attr->type,
						 wpabuf_head(attr->val),
						 wpabuf_len(attr->val))) {
				wpa_printf(MSG_ERROR, "Could not add RADIUS attribute");
				radius_msg_free(msg);
				return NULL;
			}
		}
	}

	if (radius_msg_finish_srv(msg, (u8 *) client->shared_secret,
				  client->shared_secret_len,
				  hdr->authenticator) < 0) {
		RADIUS_DEBUG("Failed to add Message-Authenticator attribute");
	}

	return msg;
}