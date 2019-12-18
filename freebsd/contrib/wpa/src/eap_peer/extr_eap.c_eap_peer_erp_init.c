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
struct eap_erp_key {char* keyname_nai; size_t rRK_len; size_t rIK_len; int /*<<< orphan*/  list; struct eap_erp_key* rIK; struct eap_erp_key* rRK; } ;
typedef  struct eap_erp_key u8 ;
struct eap_sm {size_t eapSessionIdLen; int /*<<< orphan*/  erp_keys; struct eap_erp_key* eapSessionId; int /*<<< orphan*/  eap_method_priv; TYPE_1__* m; } ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_2__ {struct eap_erp_key* (* get_emsk ) (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int EAP_EMSK_NAME_LEN ; 
 struct eap_erp_key EAP_ERP_CS_HMAC_SHA256_128 ; 
 size_t ERP_MAX_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (struct eap_erp_key*,size_t) ; 
 int /*<<< orphan*/  bin_clear_free (struct eap_erp_key*,int) ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_erp_remove_keys_realm (struct eap_sm*,char*) ; 
 char* eap_home_realm (struct eap_sm*) ; 
 scalar_t__ hmac_sha256_kdf (struct eap_erp_key*,size_t,char*,struct eap_erp_key*,int,struct eap_erp_key*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,size_t) ; 
 size_t os_strlen (char*) ; 
 struct eap_erp_key* os_zalloc (int) ; 
 struct eap_erp_key* stub1 (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,struct eap_erp_key*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,struct eap_erp_key*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpa_snprintf_hex (char*,size_t,struct eap_erp_key*,int) ; 

void eap_peer_erp_init(struct eap_sm *sm, u8 *ext_session_id,
		       size_t ext_session_id_len, u8 *ext_emsk,
		       size_t ext_emsk_len)
{
#ifdef CONFIG_ERP
	u8 *emsk = NULL;
	size_t emsk_len = 0;
	u8 *session_id = NULL;
	size_t session_id_len = 0;
	u8 EMSKname[EAP_EMSK_NAME_LEN];
	u8 len[2], ctx[3];
	char *realm;
	size_t realm_len, nai_buf_len;
	struct eap_erp_key *erp = NULL;
	int pos;

	realm = eap_home_realm(sm);
	if (!realm)
		goto fail;
	realm_len = os_strlen(realm);
	wpa_printf(MSG_DEBUG, "EAP: Realm for ERP keyName-NAI: %s", realm);
	eap_erp_remove_keys_realm(sm, realm);

	nai_buf_len = 2 * EAP_EMSK_NAME_LEN + 1 + realm_len;
	if (nai_buf_len > 253) {
		/*
		 * keyName-NAI has a maximum length of 253 octet to fit in
		 * RADIUS attributes.
		 */
		wpa_printf(MSG_DEBUG,
			   "EAP: Too long realm for ERP keyName-NAI maximum length");
		goto fail;
	}
	nai_buf_len++; /* null termination */
	erp = os_zalloc(sizeof(*erp) + nai_buf_len);
	if (erp == NULL)
		goto fail;

	if (ext_emsk) {
		emsk = ext_emsk;
		emsk_len = ext_emsk_len;
	} else {
		emsk = sm->m->get_emsk(sm, sm->eap_method_priv, &emsk_len);
	}

	if (!emsk || emsk_len == 0 || emsk_len > ERP_MAX_KEY_LEN) {
		wpa_printf(MSG_DEBUG,
			   "EAP: No suitable EMSK available for ERP");
		goto fail;
	}

	wpa_hexdump_key(MSG_DEBUG, "EAP: EMSK", emsk, emsk_len);

	if (ext_session_id) {
		session_id = ext_session_id;
		session_id_len = ext_session_id_len;
	} else {
		session_id = sm->eapSessionId;
		session_id_len = sm->eapSessionIdLen;
	}

	if (!session_id || session_id_len == 0) {
		wpa_printf(MSG_DEBUG,
			   "EAP: No suitable session id available for ERP");
		goto fail;
	}

	WPA_PUT_BE16(len, EAP_EMSK_NAME_LEN);
	if (hmac_sha256_kdf(session_id, session_id_len, "EMSK", len,
			    sizeof(len), EMSKname, EAP_EMSK_NAME_LEN) < 0) {
		wpa_printf(MSG_DEBUG, "EAP: Could not derive EMSKname");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "EAP: EMSKname", EMSKname, EAP_EMSK_NAME_LEN);

	pos = wpa_snprintf_hex(erp->keyname_nai, nai_buf_len,
			       EMSKname, EAP_EMSK_NAME_LEN);
	erp->keyname_nai[pos] = '@';
	os_memcpy(&erp->keyname_nai[pos + 1], realm, realm_len);

	WPA_PUT_BE16(len, emsk_len);
	if (hmac_sha256_kdf(emsk, emsk_len,
			    "EAP Re-authentication Root Key@ietf.org",
			    len, sizeof(len), erp->rRK, emsk_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP: Could not derive rRK for ERP");
		goto fail;
	}
	erp->rRK_len = emsk_len;
	wpa_hexdump_key(MSG_DEBUG, "EAP: ERP rRK", erp->rRK, erp->rRK_len);

	ctx[0] = EAP_ERP_CS_HMAC_SHA256_128;
	WPA_PUT_BE16(&ctx[1], erp->rRK_len);
	if (hmac_sha256_kdf(erp->rRK, erp->rRK_len,
			    "Re-authentication Integrity Key@ietf.org",
			    ctx, sizeof(ctx), erp->rIK, erp->rRK_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP: Could not derive rIK for ERP");
		goto fail;
	}
	erp->rIK_len = erp->rRK_len;
	wpa_hexdump_key(MSG_DEBUG, "EAP: ERP rIK", erp->rIK, erp->rIK_len);

	wpa_printf(MSG_DEBUG, "EAP: Stored ERP keys %s", erp->keyname_nai);
	dl_list_add(&sm->erp_keys, &erp->list);
	erp = NULL;
fail:
	if (ext_emsk)
		bin_clear_free(ext_emsk, ext_emsk_len);
	else
		bin_clear_free(emsk, emsk_len);
	bin_clear_free(ext_session_id, ext_session_id_len);
	bin_clear_free(erp, sizeof(*erp));
	os_free(realm);
#endif /* CONFIG_ERP */
}