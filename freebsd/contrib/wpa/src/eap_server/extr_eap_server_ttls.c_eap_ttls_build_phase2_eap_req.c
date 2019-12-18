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
struct eap_ttls_data {int /*<<< orphan*/  ssl; int /*<<< orphan*/  phase2_priv; TYPE_1__* phase2_method; } ;
struct eap_sm {int dummy; } ;
struct TYPE_2__ {struct wpabuf* (* buildReq ) (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RADIUS_ATTR_EAP_MESSAGE ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf*) ; 
 struct wpabuf* eap_ttls_avp_encapsulate (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 struct wpabuf* stub1 (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * eap_ttls_build_phase2_eap_req(
	struct eap_sm *sm, struct eap_ttls_data *data, u8 id)
{
	struct wpabuf *buf, *encr_req;


	buf = data->phase2_method->buildReq(sm, data->phase2_priv, id);
	if (buf == NULL)
		return NULL;

	wpa_hexdump_buf_key(MSG_DEBUG,
			    "EAP-TTLS/EAP: Encapsulate Phase 2 data", buf);

	buf = eap_ttls_avp_encapsulate(buf, RADIUS_ATTR_EAP_MESSAGE, 1);
	if (buf == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/EAP: Failed to encapsulate "
			   "packet");
		return NULL;
	}

	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-TTLS/EAP: Encrypt encapsulated "
			    "Phase 2 data", buf);

	encr_req = eap_server_tls_encrypt(sm, &data->ssl, buf);
	wpabuf_free(buf);

	return encr_req;
}