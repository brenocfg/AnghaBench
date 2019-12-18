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
struct x509_name {int dummy; } ;
struct asn1_hdr {int length; scalar_t__ class; int tag; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_CONTEXT_SPECIFIC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int x509_parse_alt_name_dns (struct x509_name*,int /*<<< orphan*/ *,int) ; 
 int x509_parse_alt_name_ip (struct x509_name*,int /*<<< orphan*/ *,int) ; 
 int x509_parse_alt_name_rfc8222 (struct x509_name*,int /*<<< orphan*/ *,int) ; 
 int x509_parse_alt_name_rid (struct x509_name*,int /*<<< orphan*/ *,int) ; 
 int x509_parse_alt_name_uri (struct x509_name*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int x509_parse_ext_alt_name(struct x509_name *name,
				   const u8 *pos, size_t len)
{
	struct asn1_hdr hdr;
	const u8 *p, *end;

	/*
	 * GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
	 *
	 * GeneralName ::= CHOICE {
	 *     otherName                       [0]     OtherName,
	 *     rfc822Name                      [1]     IA5String,
	 *     dNSName                         [2]     IA5String,
	 *     x400Address                     [3]     ORAddress,
	 *     directoryName                   [4]     Name,
	 *     ediPartyName                    [5]     EDIPartyName,
	 *     uniformResourceIdentifier       [6]     IA5String,
	 *     iPAddress                       [7]     OCTET STRING,
	 *     registeredID                    [8]     OBJECT IDENTIFIER }
	 *
	 * OtherName ::= SEQUENCE {
	 *     type-id    OBJECT IDENTIFIER,
	 *     value      [0] EXPLICIT ANY DEFINED BY type-id }
	 *
	 * EDIPartyName ::= SEQUENCE {
	 *     nameAssigner            [0]     DirectoryString OPTIONAL,
	 *     partyName               [1]     DirectoryString }
	 */

	for (p = pos, end = pos + len; p < end; p = hdr.payload + hdr.length) {
		int res;

		if (asn1_get_next(p, end - p, &hdr) < 0) {
			wpa_printf(MSG_DEBUG, "X509: Failed to parse "
				   "SubjectAltName item");
			return -1;
		}

		if (hdr.class != ASN1_CLASS_CONTEXT_SPECIFIC)
			continue;

		switch (hdr.tag) {
		case 1:
			res = x509_parse_alt_name_rfc8222(name, hdr.payload,
							  hdr.length);
			break;
		case 2:
			res = x509_parse_alt_name_dns(name, hdr.payload,
						      hdr.length);
			break;
		case 6:
			res = x509_parse_alt_name_uri(name, hdr.payload,
						      hdr.length);
			break;
		case 7:
			res = x509_parse_alt_name_ip(name, hdr.payload,
						     hdr.length);
			break;
		case 8:
			res = x509_parse_alt_name_rid(name, hdr.payload,
						      hdr.length);
			break;
		case 0: /* TODO: otherName */
		case 3: /* TODO: x500Address */
		case 4: /* TODO: directoryName */
		case 5: /* TODO: ediPartyName */
		default:
			res = 0;
			break;
		}
		if (res < 0)
			return res;
	}

	return 0;
}