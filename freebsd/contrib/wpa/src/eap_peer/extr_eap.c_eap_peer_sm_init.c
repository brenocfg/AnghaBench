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
typedef  int /*<<< orphan*/  tlsconf ;
struct tls_config {int fips_mode; int /*<<< orphan*/  cert_in_cb; struct eap_sm* cb_ctx; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; } ;
struct eapol_callbacks {int dummy; } ;
struct eap_sm {int /*<<< orphan*/ * ssl_ctx2; int /*<<< orphan*/ * ssl_ctx; int /*<<< orphan*/  erp_keys; int /*<<< orphan*/  wps; int /*<<< orphan*/  ClientTimeout; void* msg_ctx; struct eapol_callbacks const* eapol_cb; void* eapol_ctx; } ;
struct eap_config {int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CLIENT_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_peer_sm_tls_event ; 
 int /*<<< orphan*/  os_free (struct eap_sm*) ; 
 int /*<<< orphan*/  os_memset (struct tls_config*,int /*<<< orphan*/ ,int) ; 
 struct eap_sm* os_zalloc (int) ; 
 void* tls_init (struct tls_config*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct eap_sm * eap_peer_sm_init(void *eapol_ctx,
				 const struct eapol_callbacks *eapol_cb,
				 void *msg_ctx, struct eap_config *conf)
{
	struct eap_sm *sm;
	struct tls_config tlsconf;

	sm = os_zalloc(sizeof(*sm));
	if (sm == NULL)
		return NULL;
	sm->eapol_ctx = eapol_ctx;
	sm->eapol_cb = eapol_cb;
	sm->msg_ctx = msg_ctx;
	sm->ClientTimeout = EAP_CLIENT_TIMEOUT_DEFAULT;
	sm->wps = conf->wps;
	dl_list_init(&sm->erp_keys);

	os_memset(&tlsconf, 0, sizeof(tlsconf));
	tlsconf.opensc_engine_path = conf->opensc_engine_path;
	tlsconf.pkcs11_engine_path = conf->pkcs11_engine_path;
	tlsconf.pkcs11_module_path = conf->pkcs11_module_path;
	tlsconf.openssl_ciphers = conf->openssl_ciphers;
#ifdef CONFIG_FIPS
	tlsconf.fips_mode = 1;
#endif /* CONFIG_FIPS */
	tlsconf.event_cb = eap_peer_sm_tls_event;
	tlsconf.cb_ctx = sm;
	tlsconf.cert_in_cb = conf->cert_in_cb;
	sm->ssl_ctx = tls_init(&tlsconf);
	if (sm->ssl_ctx == NULL) {
		wpa_printf(MSG_WARNING, "SSL: Failed to initialize TLS "
			   "context.");
		os_free(sm);
		return NULL;
	}

	sm->ssl_ctx2 = tls_init(&tlsconf);
	if (sm->ssl_ctx2 == NULL) {
		wpa_printf(MSG_INFO, "SSL: Failed to initialize TLS "
			   "context (2).");
		/* Run without separate TLS context within TLS tunnel */
	}

	return sm;
}