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
struct x509_certificate {int dummy; } ;
struct tlsv1_client {int dummy; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; int /*<<< orphan*/ * payload; } ;
typedef  enum tls_ocsp_result { ____Placeholder_tls_ocsp_result } tls_ocsp_result ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TLS_OCSP_INVALID ; 
 int TLS_OCSP_NO_RESPONSE ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 scalar_t__ tls_process_ocsp_single_response (struct tlsv1_client*,struct x509_certificate*,struct x509_certificate*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum tls_ocsp_result
tls_process_ocsp_responses(struct tlsv1_client *conn,
			   struct x509_certificate *cert,
			   struct x509_certificate *issuer, const u8 *resp,
			   size_t len)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end;
	enum tls_ocsp_result res;

	pos = resp;
	end = resp + len;
	while (pos < end) {
		/* SingleResponse ::= SEQUENCE */
		if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
		    hdr.class != ASN1_CLASS_UNIVERSAL ||
		    hdr.tag != ASN1_TAG_SEQUENCE) {
			wpa_printf(MSG_DEBUG,
				   "OCSP: Expected SEQUENCE (SingleResponse) - found class %d tag 0x%x",
				   hdr.class, hdr.tag);
			return TLS_OCSP_INVALID;
		}
		if (tls_process_ocsp_single_response(conn, cert, issuer,
						     hdr.payload, hdr.length,
						     &res) == 0)
			return res;
		pos = hdr.payload + hdr.length;
	}

	wpa_printf(MSG_DEBUG,
		   "OCSP: Did not find a response matching the server certificate");
	return TLS_OCSP_NO_RESPONSE;
}