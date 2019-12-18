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
typedef  scalar_t__ u8 ;
struct x509_certificate {int public_key_len; int /*<<< orphan*/ * public_key; int /*<<< orphan*/  public_key_alg; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; scalar_t__* payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_BITSTRING ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ asn1_get_next (scalar_t__ const*,int,struct asn1_hdr*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ x509_parse_algorithm_identifier (scalar_t__ const*,int,int /*<<< orphan*/ *,scalar_t__ const**) ; 

__attribute__((used)) static int x509_parse_public_key(const u8 *buf, size_t len,
				 struct x509_certificate *cert,
				 const u8 **next)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end;

	/*
	 * SubjectPublicKeyInfo ::= SEQUENCE {
	 *     algorithm            AlgorithmIdentifier,
	 *     subjectPublicKey     BIT STRING
	 * }
	 */

	pos = buf;
	end = buf + len;

	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Expected SEQUENCE "
			   "(SubjectPublicKeyInfo) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	pos = hdr.payload;

	if (hdr.length > end - pos)
		return -1;
	end = pos + hdr.length;
	*next = end;

	if (x509_parse_algorithm_identifier(pos, end - pos,
					    &cert->public_key_alg, &pos))
		return -1;

	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_BITSTRING) {
		wpa_printf(MSG_DEBUG, "X509: Expected BITSTRING "
			   "(subjectPublicKey) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	if (hdr.length < 1)
		return -1;
	pos = hdr.payload;
	if (*pos) {
		wpa_printf(MSG_DEBUG, "X509: BITSTRING - %d unused bits",
			   *pos);
		/*
		 * TODO: should this be rejected? X.509 certificates are
		 * unlikely to use such a construction. Now we would end up
		 * including the extra bits in the buffer which may also be
		 * ok.
		 */
	}
	os_free(cert->public_key);
	cert->public_key = os_memdup(pos + 1, hdr.length - 1);
	if (cert->public_key == NULL) {
		wpa_printf(MSG_DEBUG, "X509: Failed to allocate memory for "
			   "public key");
		return -1;
	}
	cert->public_key_len = hdr.length - 1;
	wpa_hexdump(MSG_MSGDUMP, "X509: subjectPublicKey",
		    cert->public_key, cert->public_key_len);

	return 0;
}