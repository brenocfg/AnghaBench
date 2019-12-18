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
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_INITIATE ; 
 size_t EAP_ERP_TLV_DOMAIN_NAME ; 
 scalar_t__ EAP_ERP_TYPE_REAUTH_START ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 char* eap_get_erp_domain (struct eap_sm*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_sm_buildInitiateReauthStart(struct eap_sm *sm,
						       u8 id)
{
	const char *domain;
	size_t plen = 1;
	struct wpabuf *msg;
	size_t domain_len = 0;

	domain = eap_get_erp_domain(sm);
	if (domain) {
		domain_len = os_strlen(domain);
		plen += 2 + domain_len;
	}

	msg = eap_msg_alloc(EAP_VENDOR_IETF,
			    (EapType) EAP_ERP_TYPE_REAUTH_START, plen,
			    EAP_CODE_INITIATE, id);
	if (msg == NULL)
		return NULL;
	wpabuf_put_u8(msg, 0); /* Reserved */
	if (domain) {
		/* Domain name TLV */
		wpabuf_put_u8(msg, EAP_ERP_TLV_DOMAIN_NAME);
		wpabuf_put_u8(msg, domain_len);
		wpabuf_put_data(msg, domain, domain_len);
	}

	return msg;
}