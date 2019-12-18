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
struct asn1_hdr {int length; int* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int asn1_valid_der_boolean(struct asn1_hdr *hdr)
{
	/* Enforce DER requirements for a single way of encoding a BOOLEAN */
	if (hdr->length != 1) {
		wpa_printf(MSG_DEBUG, "ASN.1: Unexpected BOOLEAN length (%u)",
			   hdr->length);
		return 0;
	}

	if (hdr->payload[0] != 0 && hdr->payload[0] != 0xff) {
		wpa_printf(MSG_DEBUG,
			   "ASN.1: Invalid BOOLEAN value 0x%x (DER requires 0 or 0xff)",
			   hdr->payload[0]);
		return 0;
	}

	return 1;
}