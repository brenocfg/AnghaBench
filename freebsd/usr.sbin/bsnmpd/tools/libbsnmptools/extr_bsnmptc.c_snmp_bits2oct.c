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
typedef  int /*<<< orphan*/  v ;
typedef  int uint64_t ;
struct asn_oid {int dummy; } ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 int errno ; 
 scalar_t__ snmp_suboid_append (struct asn_oid*,int /*<<< orphan*/ ) ; 
 int strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static char *
snmp_bits2oct(char *str, struct asn_oid *oid)
{
	char *endptr;
	int i, size, bits, saved_errno;
	uint64_t v, mask = 0xFF00000000000000;

	saved_errno = errno;
	errno = 0;

	v = strtoull(str, &endptr, 16);
	if (errno != 0) {
		warn("Bad BITS value %s", str);
		errno = saved_errno;
		return (NULL);
	}

	bits = 8;
	/* Determine length - up to 8 octets supported so far. */
	for (size = sizeof(v); size > 0; size--) {
		if ((v & mask) != 0)
			break;
		mask = mask >> bits;
	}

	if (size == 0)
		size = 1;

	if (snmp_suboid_append(oid, (asn_subid_t) size) < 0)
		return (NULL);

	for (i = 0, bits = 0; i < size; i++, bits += 8)
		if (snmp_suboid_append(oid,
		    (asn_subid_t)((v & mask) >> bits)) < 0)
			return (NULL);

	return (endptr);
}