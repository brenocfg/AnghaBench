#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_pwd_id {scalar_t__ random_function; scalar_t__ prf; scalar_t__ prep; int /*<<< orphan*/  identity; int /*<<< orphan*/  token; int /*<<< orphan*/  group_num; } ;
struct eap_pwd_data {scalar_t__ group_num; scalar_t__ password_prep; size_t id_peer_len; size_t password_len; TYPE_1__* grp; int /*<<< orphan*/  token; int /*<<< orphan*/ * id_peer; int /*<<< orphan*/  id_server_len; int /*<<< orphan*/  id_server; int /*<<< orphan*/ * password; } ;
typedef  int /*<<< orphan*/  pwhashhash ;
struct TYPE_3__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 scalar_t__ EAP_PWD_DEFAULT_PRF ; 
 scalar_t__ EAP_PWD_DEFAULT_RAND_FUNC ; 
 scalar_t__ EAP_PWD_PREP_MS ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  PWD_Commit_Req ; 
 scalar_t__ be_to_host16 (int /*<<< orphan*/ ) ; 
 int compute_password_element (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_ec_prime_len_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* get_eap_pwd_group (scalar_t__) ; 
 int hash_nt_password_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_pwd_process_id_resp(struct eap_sm *sm,
				    struct eap_pwd_data *data,
				    const u8 *payload, size_t payload_len)
{
	struct eap_pwd_id *id;
	const u8 *password;
	size_t password_len;
	u8 pwhashhash[16];
	int res;

	if (payload_len < sizeof(struct eap_pwd_id)) {
		wpa_printf(MSG_INFO, "EAP-pwd: Invalid ID response");
		return;
	}

	id = (struct eap_pwd_id *) payload;
	if ((data->group_num != be_to_host16(id->group_num)) ||
	    (id->random_function != EAP_PWD_DEFAULT_RAND_FUNC) ||
	    (os_memcmp(id->token, (u8 *)&data->token, sizeof(data->token))) ||
	    (id->prf != EAP_PWD_DEFAULT_PRF) ||
	    (id->prep != data->password_prep)) {
		wpa_printf(MSG_INFO, "EAP-pwd: peer changed parameters");
		eap_pwd_state(data, FAILURE);
		return;
	}
	if (data->id_peer || data->grp) {
		wpa_printf(MSG_INFO, "EAP-pwd: data was already allocated");
		return;
	}
	data->id_peer = os_malloc(payload_len - sizeof(struct eap_pwd_id));
	if (data->id_peer == NULL) {
		wpa_printf(MSG_INFO, "EAP-PWD: memory allocation id fail");
		return;
	}
	data->id_peer_len = payload_len - sizeof(struct eap_pwd_id);
	os_memcpy(data->id_peer, id->identity, data->id_peer_len);
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-PWD (server): peer sent id of",
			  data->id_peer, data->id_peer_len);

	data->grp = get_eap_pwd_group(data->group_num);
	if (data->grp == NULL) {
		wpa_printf(MSG_INFO, "EAP-PWD: failed to allocate memory for "
			   "group");
		return;
	}

	/*
	 * If it's PREP_MS then hash the password again, otherwise regardless
	 * of the prep the client is doing, the password we have is the one to
	 * use to generate the password element.
	 */
	if (data->password_prep == EAP_PWD_PREP_MS) {
		res = hash_nt_password_hash(data->password, pwhashhash);
		if (res)
			return;
		password = pwhashhash;
		password_len = sizeof(pwhashhash);
	} else {
		password = data->password;
		password_len = data->password_len;
	}

	res = compute_password_element(data->grp, data->group_num,
				       password, password_len,
				       data->id_server, data->id_server_len,
				       data->id_peer, data->id_peer_len,
				       (u8 *) &data->token);
	forced_memzero(pwhashhash, sizeof(pwhashhash));
	if (res) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): unable to compute "
			   "PWE");
		return;
	}
	wpa_printf(MSG_DEBUG, "EAP-PWD (server): computed %d bit PWE...",
		   (int) crypto_ec_prime_len_bits(data->grp->group));

	eap_pwd_state(data, PWD_Commit_Req);
}