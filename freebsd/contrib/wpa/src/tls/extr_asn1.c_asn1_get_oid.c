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
struct asn1_oid {int dummy; } ;
struct asn1_hdr {scalar_t__ length; scalar_t__ class; scalar_t__ tag; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_OID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 int asn1_parse_oid (int /*<<< orphan*/ *,int,struct asn1_oid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

int asn1_get_oid(const u8 *buf, size_t len, struct asn1_oid *oid,
		 const u8 **next)
{
	struct asn1_hdr hdr;

	if (asn1_get_next(buf, len, &hdr) < 0 || hdr.length == 0)
		return -1;

	if (hdr.class != ASN1_CLASS_UNIVERSAL || hdr.tag != ASN1_TAG_OID) {
		wpa_printf(MSG_DEBUG, "ASN.1: Expected OID - found class %d "
			   "tag 0x%x", hdr.class, hdr.tag);
		return -1;
	}

	*next = hdr.payload + hdr.length;

	return asn1_parse_oid(hdr.payload, hdr.length, oid);
}