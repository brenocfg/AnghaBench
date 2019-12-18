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
typedef  scalar_t__ uint32_t ;
struct asn_oid {int dummy; } ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 scalar_t__ ASN_MAXOIDLEN ; 
 scalar_t__ snmp_suboid_append (struct asn_oid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static char *
snmp_str2asn_oid(char *str, struct asn_oid *oid)
{
	uint32_t i, len = 0;

	/*
	 * OctetStrings are allowed max length of ASN_MAXOCTETSTRING,
	 * but trying to index an entry with such a long OctetString
	 * will fail anyway.
	 */
	for (len = 0; len < ASN_MAXOIDLEN; len++) {
		if (strchr(",]", *(str + len)) != NULL)
			break;
	}

	if (len >= ASN_MAXOIDLEN)
		return (NULL);

	if (snmp_suboid_append(oid, (asn_subid_t) len) < 0)
		return (NULL);

	for (i = 0; i < len; i++)
		if (snmp_suboid_append(oid, (asn_subid_t) *(str + i)) < 0)
			return (NULL);

	return (str + len);
}