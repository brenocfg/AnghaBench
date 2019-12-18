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
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ x509_parse_extension (struct x509_certificate*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int x509_parse_extensions(struct x509_certificate *cert,
				 const u8 *pos, size_t len)
{
	const u8 *end;
	struct asn1_hdr hdr;

	/* Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension */

	if (asn1_get_next(pos, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "X509: Unexpected ASN.1 data "
			   "for Extensions: class %d tag 0x%x; "
			   "expected SEQUENCE", hdr.class, hdr.tag);
		return -1;
	}

	pos = hdr.payload;
	end = pos + hdr.length;

	while (pos < end) {
		if (x509_parse_extension(cert, pos, end - pos, &pos)
		    < 0)
			return -1;
	}

	return 0;
}