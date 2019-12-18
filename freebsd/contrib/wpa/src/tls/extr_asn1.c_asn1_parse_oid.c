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
typedef  int u8 ;
struct asn1_oid {scalar_t__ len; unsigned long* oid; } ;

/* Variables and functions */
 scalar_t__ ASN1_MAX_OID_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (struct asn1_oid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int asn1_parse_oid(const u8 *buf, size_t len, struct asn1_oid *oid)
{
	const u8 *pos, *end;
	unsigned long val;
	u8 tmp;

	os_memset(oid, 0, sizeof(*oid));

	pos = buf;
	end = buf + len;

	while (pos < end) {
		val = 0;

		do {
			if (pos >= end)
				return -1;
			tmp = *pos++;
			val = (val << 7) | (tmp & 0x7f);
		} while (tmp & 0x80);

		if (oid->len >= ASN1_MAX_OID_LEN) {
			wpa_printf(MSG_DEBUG, "ASN.1: Too long OID value");
			return -1;
		}
		if (oid->len == 0) {
			/*
			 * The first octet encodes the first two object
			 * identifier components in (X*40) + Y formula.
			 * X = 0..2.
			 */
			oid->oid[0] = val / 40;
			if (oid->oid[0] > 2)
				oid->oid[0] = 2;
			oid->oid[1] = val - oid->oid[0] * 40;
			oid->len = 2;
		} else
			oid->oid[oid->len++] = val;
	}

	return 0;
}