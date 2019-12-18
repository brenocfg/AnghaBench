#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eap_server_erp_key {char* keyname_nai; size_t rRK_len; size_t rIK_len; struct eap_server_erp_key* rIK; struct eap_server_erp_key* rRK; scalar_t__ recv_seq; } ;
typedef  struct eap_server_erp_key u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {size_t eapSessionIdLen; struct eap_server_erp_key* eapSessionId; } ;
struct eap_sm {TYPE_2__ eap_if; int /*<<< orphan*/  eap_method_priv; TYPE_1__* m; } ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_3__ {struct eap_server_erp_key* (* get_emsk ) (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int EAP_EMSK_NAME_LEN ; 
 struct eap_server_erp_key EAP_ERP_CS_HMAC_SHA256_128 ; 
 size_t ERP_MAX_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (struct eap_server_erp_key*,size_t) ; 
 int /*<<< orphan*/  bin_clear_free (struct eap_server_erp_key*,int) ; 
 scalar_t__ eap_erp_add_key (struct eap_sm*,struct eap_server_erp_key*) ; 
 char* eap_get_erp_domain (struct eap_sm*) ; 
 scalar_t__ hmac_sha256_kdf (struct eap_server_erp_key*,size_t,char*,struct eap_server_erp_key*,int,struct eap_server_erp_key*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 
 struct eap_server_erp_key* os_zalloc (int) ; 
 struct eap_server_erp_key* stub1 (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,struct eap_server_erp_key*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,struct eap_server_erp_key*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpa_snprintf_hex (char*,size_t,struct eap_server_erp_key*,int) ; 

__attribute__((used)) static void eap_server_erp_init(struct eap_sm *sm)
{
#ifdef CONFIG_ERP
	u8 *emsk = NULL;
	size_t emsk_len = 0;
	u8 EMSKname[EAP_EMSK_NAME_LEN];
	u8 len[2], ctx[3];
	const char *domain;
	size_t domain_len, nai_buf_len;
	struct eap_server_erp_key *erp = NULL;
	int pos;

	domain = eap_get_erp_domain(sm);
	if (!domain)
		return;

	domain_len = os_strlen(domain);

	nai_buf_len = 2 * EAP_EMSK_NAME_LEN + 1 + domain_len;
	if (nai_buf_len > 253) {
		/*
		 * keyName-NAI has a maximum length of 253 octet to fit in
		 * RADIUS attributes.
		 */
		wpa_printf(MSG_DEBUG,
			   "EAP: Too long realm for ERP keyName-NAI maximum length");
		return;
	}
	nai_buf_len++; /* null termination */
	erp = os_zalloc(sizeof(*erp) + nai_buf_len);
	if (erp == NULL)
		goto fail;
	erp->recv_seq = (u32) -1;

	emsk = sm->m->get_emsk(sm, sm->eap_method_priv, &emsk_len);
	if (!emsk || emsk_len == 0 || emsk_len > ERP_MAX_KEY_LEN) {
		wpa_printf(MSG_DEBUG,
			   "EAP: No suitable EMSK available for ERP");
		goto fail;
	}

	wpa_hexdump_key(MSG_DEBUG, "EAP: EMSK", emsk, emsk_len);

	WPA_PUT_BE16(len, EAP_EMSK_NAME_LEN);
	if (hmac_sha256_kdf(sm->eap_if.eapSessionId, sm->eap_if.eapSessionIdLen,
			    "EMSK", len, sizeof(len),
			    EMSKname, EAP_EMSK_NAME_LEN) < 0) {
		wpa_printf(MSG_DEBUG, "EAP: Could not derive EMSKname");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "EAP: EMSKname", EMSKname, EAP_EMSK_NAME_LEN);

	pos = wpa_snprintf_hex(erp->keyname_nai, nai_buf_len,
			       EMSKname, EAP_EMSK_NAME_LEN);
	erp->keyname_nai[pos] = '@';
	os_memcpy(&erp->keyname_nai[pos + 1], domain, domain_len);

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

	if (eap_erp_add_key(sm, erp) == 0) {
		wpa_printf(MSG_DEBUG, "EAP: Stored ERP keys %s",
			   erp->keyname_nai);
		erp = NULL;
	}

fail:
	bin_clear_free(emsk, emsk_len);
	bin_clear_free(erp, sizeof(*erp));
#endif /* CONFIG_ERP */
}