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
typedef  int /*<<< orphan*/  const u8 ;
struct x509_certificate {int /*<<< orphan*/  extensions_present; int /*<<< orphan*/  ext_key_usage; } ;
struct asn1_oid {int dummy; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; int /*<<< orphan*/  const* payload; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  X509_EXT_EXT_KEY_USAGE ; 
 int /*<<< orphan*/  X509_EXT_KEY_USAGE_ANY ; 
 int /*<<< orphan*/  X509_EXT_KEY_USAGE_CLIENT_AUTH ; 
 int /*<<< orphan*/  X509_EXT_KEY_USAGE_OCSP ; 
 int /*<<< orphan*/  X509_EXT_KEY_USAGE_SERVER_AUTH ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 scalar_t__ asn1_get_oid (int /*<<< orphan*/  const*,int,struct asn1_oid*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  asn1_oid_to_str (struct asn1_oid*,char*,int) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ x509_any_ext_key_usage_oid (struct asn1_oid*) ; 
 scalar_t__ x509_id_kp_client_auth_oid (struct asn1_oid*) ; 
 scalar_t__ x509_id_kp_ocsp_oid (struct asn1_oid*) ; 
 scalar_t__ x509_id_kp_server_auth_oid (struct asn1_oid*) ; 

__attribute__((used)) static int x509_parse_ext_ext_key_usage(struct x509_certificate *cert,
					const u8 *pos, size_t len)
{
	struct asn1_hdr hdr;
	const u8 *end;
	struct asn1_oid oid;

	/*
	 * ExtKeyUsageSyntax ::= SEQUENCE SIZE (1..MAX) OF KeyPurposeId
	 *
	 * KeyPurposeId ::= OBJECT IDENTIFIER
	 */

	if (asn1_get_next(pos, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE "
			   "(ExtKeyUsageSyntax) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	if (hdr.length > pos + len - hdr.payload)
		return -1;
	pos = hdr.payload;
	end = pos + hdr.length;

	wpa_hexdump(MSG_MSGDUMP, "X509: ExtKeyUsageSyntax", pos, end - pos);

	while (pos < end) {
		char buf[80];

		if (asn1_get_oid(pos, end - pos, &oid, &pos))
			return -1;
		if (x509_any_ext_key_usage_oid(&oid)) {
			os_strlcpy(buf, "anyExtendedKeyUsage", sizeof(buf));
			cert->ext_key_usage |= X509_EXT_KEY_USAGE_ANY;
		} else if (x509_id_kp_server_auth_oid(&oid)) {
			os_strlcpy(buf, "id-kp-serverAuth", sizeof(buf));
			cert->ext_key_usage |= X509_EXT_KEY_USAGE_SERVER_AUTH;
		} else if (x509_id_kp_client_auth_oid(&oid)) {
			os_strlcpy(buf, "id-kp-clientAuth", sizeof(buf));
			cert->ext_key_usage |= X509_EXT_KEY_USAGE_CLIENT_AUTH;
		} else if (x509_id_kp_ocsp_oid(&oid)) {
			os_strlcpy(buf, "id-kp-OCSPSigning", sizeof(buf));
			cert->ext_key_usage |= X509_EXT_KEY_USAGE_OCSP;
		} else {
			asn1_oid_to_str(&oid, buf, sizeof(buf));
		}
		wpa_printf(MSG_DEBUG, "ExtKeyUsage KeyPurposeId: %s", buf);
	}

	cert->extensions_present |= X509_EXT_EXT_KEY_USAGE;

	return 0;
}