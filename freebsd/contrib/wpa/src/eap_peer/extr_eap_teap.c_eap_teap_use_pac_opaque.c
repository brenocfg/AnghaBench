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
struct teap_tlv_hdr {void* length; void* tlv_type; } ;
struct eap_teap_pac {size_t pac_opaque_len; int /*<<< orphan*/  pac_opaque; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_teap_data {TYPE_1__ ssl; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t PAC_TYPE_PAC_OPAQUE ; 
 int /*<<< orphan*/  TLS_EXT_PAC_OPAQUE ; 
 void* host_to_be16 (size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (struct teap_tlv_hdr*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ tls_connection_client_hello_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_teap_use_pac_opaque(struct eap_sm *sm,
				   struct eap_teap_data *data,
				   struct eap_teap_pac *pac)
{
	u8 *tlv;
	size_t tlv_len, olen;
	struct teap_tlv_hdr *ehdr;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add PAC-Opaque TLS extension");
	olen = pac->pac_opaque_len;
	tlv_len = sizeof(*ehdr) + olen;
	tlv = os_malloc(tlv_len);
	if (tlv) {
		ehdr = (struct teap_tlv_hdr *) tlv;
		ehdr->tlv_type = host_to_be16(PAC_TYPE_PAC_OPAQUE);
		ehdr->length = host_to_be16(olen);
		os_memcpy(ehdr + 1, pac->pac_opaque, olen);
	}
	if (!tlv ||
	    tls_connection_client_hello_ext(sm->ssl_ctx, data->ssl.conn,
					    TLS_EXT_PAC_OPAQUE,
					    tlv, tlv_len) < 0) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Failed to add PAC-Opaque TLS extension");
		os_free(tlv);
		return -1;
	}
	os_free(tlv);

	return 0;
}