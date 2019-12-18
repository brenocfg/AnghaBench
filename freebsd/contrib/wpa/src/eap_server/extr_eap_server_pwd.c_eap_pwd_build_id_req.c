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
struct eap_sm {int dummy; } ;
struct eap_pwd_id {int dummy; } ;
struct eap_pwd_data {int id_server_len; int password_len; int /*<<< orphan*/ * id_server; int /*<<< orphan*/ * outbuf; int /*<<< orphan*/  password_prep; int /*<<< orphan*/  token; int /*<<< orphan*/  group_num; scalar_t__ password_hash; scalar_t__ salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  password; scalar_t__ out_frag_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PWD_DEFAULT_PRF ; 
 int /*<<< orphan*/  EAP_PWD_DEFAULT_RAND_FUNC ; 
 int /*<<< orphan*/  EAP_PWD_PREP_MS ; 
 int /*<<< orphan*/  EAP_PWD_PREP_NONE ; 
 int /*<<< orphan*/  EAP_PWD_PREP_SSHA1 ; 
 int /*<<< orphan*/  EAP_PWD_PREP_SSHA256 ; 
 int /*<<< orphan*/  EAP_PWD_PREP_SSHA512 ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_pwd_build_id_req(struct eap_sm *sm, struct eap_pwd_data *data,
				 u8 id)
{
	wpa_printf(MSG_DEBUG, "EAP-pwd: ID/Request");
	/*
	 * if we're fragmenting then we already have an id request, just return
	 */
	if (data->out_frag_pos)
		return;

	data->outbuf = wpabuf_alloc(sizeof(struct eap_pwd_id) +
				    data->id_server_len);
	if (data->outbuf == NULL) {
		eap_pwd_state(data, FAILURE);
		return;
	}

	if (os_get_random((u8 *) &data->token, sizeof(data->token)) < 0) {
		wpabuf_free(data->outbuf);
		data->outbuf = NULL;
		eap_pwd_state(data, FAILURE);
		return;
	}

	wpa_hexdump_key(MSG_DEBUG, "EAP-pwd (server): password",
			data->password, data->password_len);
	if (data->salt_len)
		wpa_hexdump(MSG_DEBUG, "EAP-pwd (server): salt",
			    data->salt, data->salt_len);

	/*
	 * If this is a salted password then figure out how it was hashed
	 * based on the length.
	 */
	if (data->salt_len) {
		switch (data->password_len) {
		case 20:
			data->password_prep = EAP_PWD_PREP_SSHA1;
			break;
		case 32:
			data->password_prep = EAP_PWD_PREP_SSHA256;
			break;
		case 64:
			data->password_prep = EAP_PWD_PREP_SSHA512;
			break;
		default:
			wpa_printf(MSG_INFO,
				   "EAP-pwd (server): bad size %d for salted password",
				   (int) data->password_len);
			eap_pwd_state(data, FAILURE);
			return;
		}
	} else {
		/* Otherwise, figure out whether it's MS hashed or plain */
		data->password_prep = data->password_hash ? EAP_PWD_PREP_MS :
			EAP_PWD_PREP_NONE;
	}

	wpabuf_put_be16(data->outbuf, data->group_num);
	wpabuf_put_u8(data->outbuf, EAP_PWD_DEFAULT_RAND_FUNC);
	wpabuf_put_u8(data->outbuf, EAP_PWD_DEFAULT_PRF);
	wpabuf_put_data(data->outbuf, &data->token, sizeof(data->token));
	wpabuf_put_u8(data->outbuf, data->password_prep);
	wpabuf_put_data(data->outbuf, data->id_server, data->id_server_len);
}