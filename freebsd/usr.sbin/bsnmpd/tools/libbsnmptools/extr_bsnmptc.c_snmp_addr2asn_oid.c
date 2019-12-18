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
typedef  int uint32_t ;
struct asn_oid {int dummy; } ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 scalar_t__ SNMP_PHYSADDR_OCTETS ; 
 int errno ; 
 scalar_t__ snmp_suboid_append (struct asn_oid*,int /*<<< orphan*/ ) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static char *
snmp_addr2asn_oid(char *str, struct asn_oid *oid)
{
	char *endptr, *ptr;
	uint32_t v, i;
	int saved_errno;

	if (snmp_suboid_append(oid, (asn_subid_t) SNMP_PHYSADDR_OCTETS) < 0)
		return (NULL);

	ptr = str;
	for (i = 0; i < 5; i++) {
		saved_errno = errno;
		v = strtoul(ptr, &endptr, 16);
		errno = saved_errno;
		if (v > 0xff) {
			warnx("Integer value %s not supported", str);
			return (NULL);
		}
		if (*endptr != ':') {
			warnx("Failed adding oid - %s", str);
			return (NULL);
		}
		if (snmp_suboid_append(oid, (asn_subid_t) v) < 0)
			return (NULL);
		ptr = endptr + 1;
	}

	/* The last one - don't check the ending char here. */
	saved_errno = errno;
	v = strtoul(ptr, &endptr, 16);
	errno = saved_errno;
	if (v > 0xff) {
		warnx("Integer value %s not supported", str);
		return (NULL);
	}
	if (snmp_suboid_append(oid, (asn_subid_t) v) < 0)
		return (NULL);

	return (endptr);
}