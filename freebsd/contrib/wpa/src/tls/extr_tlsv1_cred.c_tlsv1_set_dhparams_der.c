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
struct tlsv1_credentials {scalar_t__ dh_p_len; scalar_t__ dh_g_len; int /*<<< orphan*/ * dh_g; int /*<<< orphan*/ * dh_p; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; scalar_t__ length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_INTEGER ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_memdup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tlsv1_set_dhparams_der(struct tlsv1_credentials *cred,
				  const u8 *dh, size_t len)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end;

	pos = dh;
	end = dh + len;

	/*
	 * DHParameter ::= SEQUENCE {
	 *   prime INTEGER, -- p
	 *   base INTEGER, -- g
	 *   privateValueLength INTEGER OPTIONAL }
	 */

	/* DHParamer ::= SEQUENCE */
	if (asn1_get_next(pos, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "DH: DH parameters did not start with a "
			   "valid SEQUENCE - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return -1;
	}
	pos = hdr.payload;

	/* prime INTEGER */
	if (asn1_get_next(pos, end - pos, &hdr) < 0)
		return -1;

	if (hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_INTEGER) {
		wpa_printf(MSG_DEBUG, "DH: No INTEGER tag found for p; "
			   "class=%d tag=0x%x", hdr.class, hdr.tag);
		return -1;
	}

	wpa_hexdump(MSG_MSGDUMP, "DH: prime (p)", hdr.payload, hdr.length);
	if (hdr.length == 0)
		return -1;
	os_free(cred->dh_p);
	cred->dh_p = os_memdup(hdr.payload, hdr.length);
	if (cred->dh_p == NULL)
		return -1;
	cred->dh_p_len = hdr.length;
	pos = hdr.payload + hdr.length;

	/* base INTEGER */
	if (asn1_get_next(pos, end - pos, &hdr) < 0)
		return -1;

	if (hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_INTEGER) {
		wpa_printf(MSG_DEBUG, "DH: No INTEGER tag found for g; "
			   "class=%d tag=0x%x", hdr.class, hdr.tag);
		return -1;
	}

	wpa_hexdump(MSG_MSGDUMP, "DH: base (g)", hdr.payload, hdr.length);
	if (hdr.length == 0)
		return -1;
	os_free(cred->dh_g);
	cred->dh_g = os_memdup(hdr.payload, hdr.length);
	if (cred->dh_g == NULL)
		return -1;
	cred->dh_g_len = hdr.length;

	return 0;
}