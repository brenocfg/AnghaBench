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
struct eap_sm {int /*<<< orphan*/  eap_method_priv; TYPE_1__* m; } ;
struct eap_peer_config {size_t anonymous_identity_len; size_t identity_len; int /*<<< orphan*/ * identity; scalar_t__ pcsc; int /*<<< orphan*/ * anonymous_identity; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* get_identity ) (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_IDENTITY ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ eap_sm_get_scard_identity (struct eap_sm*,struct eap_peer_config*) ; 
 int /*<<< orphan*/  eap_sm_request_identity (struct eap_sm*) ; 
 scalar_t__ eap_sm_set_scard_pin (struct eap_sm*,struct eap_peer_config*) ; 
 int /*<<< orphan*/ * stub1 (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 

struct wpabuf * eap_sm_buildIdentity(struct eap_sm *sm, int id, int encrypted)
{
	struct eap_peer_config *config = eap_get_config(sm);
	struct wpabuf *resp;
	const u8 *identity;
	size_t identity_len;

	if (config == NULL) {
		wpa_printf(MSG_WARNING, "EAP: buildIdentity: configuration "
			   "was not available");
		return NULL;
	}

	if (sm->m && sm->m->get_identity &&
	    (identity = sm->m->get_identity(sm, sm->eap_method_priv,
					    &identity_len)) != NULL) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP: using method re-auth "
				  "identity", identity, identity_len);
	} else if (!encrypted && config->anonymous_identity) {
		identity = config->anonymous_identity;
		identity_len = config->anonymous_identity_len;
		wpa_hexdump_ascii(MSG_DEBUG, "EAP: using anonymous identity",
				  identity, identity_len);
	} else {
		identity = config->identity;
		identity_len = config->identity_len;
		wpa_hexdump_ascii(MSG_DEBUG, "EAP: using real identity",
				  identity, identity_len);
	}

	if (config->pcsc) {
#ifdef PCSC_FUNCS
		if (!identity) {
			if (eap_sm_get_scard_identity(sm, config) < 0)
				return NULL;
			identity = config->identity;
			identity_len = config->identity_len;
			wpa_hexdump_ascii(MSG_DEBUG,
					  "permanent identity from IMSI",
					  identity, identity_len);
		} else if (eap_sm_set_scard_pin(sm, config) < 0) {
			return NULL;
		}
#else /* PCSC_FUNCS */
		return NULL;
#endif /* PCSC_FUNCS */
	} else if (!identity) {
		wpa_printf(MSG_WARNING,
			"EAP: buildIdentity: identity configuration was not available");
		eap_sm_request_identity(sm);
		return NULL;
	}

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_IDENTITY, identity_len,
			     EAP_CODE_RESPONSE, id);
	if (resp == NULL)
		return NULL;

	wpabuf_put_data(resp, identity, identity_len);

	return resp;
}