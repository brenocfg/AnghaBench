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
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_pwd_id {scalar_t__ random_function; scalar_t__ prf; scalar_t__ prep; int /*<<< orphan*/  token; int /*<<< orphan*/  identity; int /*<<< orphan*/  group_num; } ;
struct eap_pwd_data {scalar_t__ state; scalar_t__ prep; size_t id_server_len; int id_peer_len; int /*<<< orphan*/  id_peer; int /*<<< orphan*/ * outbuf; int /*<<< orphan*/  group_num; int /*<<< orphan*/ * grp; int /*<<< orphan*/ * id_server; int /*<<< orphan*/ * token; scalar_t__ password_hash; } ;
struct eap_method_ret {void* ignore; } ;

/* Variables and functions */
 scalar_t__ EAP_PWD_DEFAULT_PRF ; 
 scalar_t__ EAP_PWD_DEFAULT_RAND_FUNC ; 
 scalar_t__ EAP_PWD_PREP_MS ; 
 scalar_t__ EAP_PWD_PREP_NONE ; 
 scalar_t__ EAP_PWD_PREP_SSHA1 ; 
 scalar_t__ EAP_PWD_PREP_SSHA256 ; 
 scalar_t__ EAP_PWD_PREP_SSHA512 ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  PWD_Commit_Req ; 
 scalar_t__ PWD_ID_Req ; 
 void* TRUE ; 
 int /*<<< orphan*/  be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_allowed_group (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_eap_pwd_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
eap_pwd_perform_id_exchange(struct eap_sm *sm, struct eap_pwd_data *data,
			    struct eap_method_ret *ret,
			    const struct wpabuf *reqData,
			    const u8 *payload, size_t payload_len)
{
	struct eap_pwd_id *id;

	if (data->state != PWD_ID_Req) {
		ret->ignore = TRUE;
		eap_pwd_state(data, FAILURE);
		return;
	}

	if (payload_len < sizeof(struct eap_pwd_id)) {
		ret->ignore = TRUE;
		eap_pwd_state(data, FAILURE);
		return;
	}

	id = (struct eap_pwd_id *) payload;
	data->group_num = be_to_host16(id->group_num);
	wpa_printf(MSG_DEBUG,
		   "EAP-PWD: Server EAP-pwd-ID proposal: group=%u random=%u prf=%u prep=%u",
		   data->group_num, id->random_function, id->prf, id->prep);
	if (id->random_function != EAP_PWD_DEFAULT_RAND_FUNC ||
	    id->prf != EAP_PWD_DEFAULT_PRF ||
	    !eap_pwd_allowed_group(data, data->group_num)) {
		wpa_printf(MSG_INFO,
			   "EAP-pwd: Unsupported or disabled proposal");
		eap_pwd_state(data, FAILURE);
		return;
	}

	if (id->prep != EAP_PWD_PREP_NONE &&
	    id->prep != EAP_PWD_PREP_MS &&
	    id->prep != EAP_PWD_PREP_SSHA1 &&
	    id->prep != EAP_PWD_PREP_SSHA256 &&
	    id->prep != EAP_PWD_PREP_SSHA512) {
		wpa_printf(MSG_DEBUG,
			   "EAP-PWD: Unsupported password pre-processing technique (Prep=%u)",
			   id->prep);
		eap_pwd_state(data, FAILURE);
		return;
	}

	if (id->prep == EAP_PWD_PREP_NONE && data->password_hash) {
		wpa_printf(MSG_DEBUG,
			   "EAP-PWD: Unhashed password not available");
		eap_pwd_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-PWD (peer): using group %d",
		   data->group_num);

	data->prep = id->prep;
	os_memcpy(data->token, id->token, sizeof(id->token));

	if (data->id_server || data->grp) {
		wpa_printf(MSG_INFO, "EAP-pwd: data was already allocated");
		eap_pwd_state(data, FAILURE);
		return;
	}

	data->id_server = os_malloc(payload_len - sizeof(struct eap_pwd_id));
	if (data->id_server == NULL) {
		wpa_printf(MSG_INFO, "EAP-PWD: memory allocation id fail");
		eap_pwd_state(data, FAILURE);
		return;
	}
	data->id_server_len = payload_len - sizeof(struct eap_pwd_id);
	os_memcpy(data->id_server, id->identity, data->id_server_len);
	wpa_hexdump_ascii(MSG_INFO, "EAP-PWD (peer): server sent id of",
			  data->id_server, data->id_server_len);

	data->grp = get_eap_pwd_group(data->group_num);
	if (data->grp == NULL) {
		wpa_printf(MSG_INFO, "EAP-PWD: failed to allocate memory for "
			   "group");
		eap_pwd_state(data, FAILURE);
		return;
	}

	data->outbuf = wpabuf_alloc(sizeof(struct eap_pwd_id) +
				    data->id_peer_len);
	if (data->outbuf == NULL) {
		eap_pwd_state(data, FAILURE);
		return;
	}
	wpabuf_put_be16(data->outbuf, data->group_num);
	wpabuf_put_u8(data->outbuf, EAP_PWD_DEFAULT_RAND_FUNC);
	wpabuf_put_u8(data->outbuf, EAP_PWD_DEFAULT_PRF);
	wpabuf_put_data(data->outbuf, id->token, sizeof(id->token));
	wpabuf_put_u8(data->outbuf, id->prep);
	wpabuf_put_data(data->outbuf, data->id_peer, data->id_peer_len);

	eap_pwd_state(data, PWD_Commit_Req);
}