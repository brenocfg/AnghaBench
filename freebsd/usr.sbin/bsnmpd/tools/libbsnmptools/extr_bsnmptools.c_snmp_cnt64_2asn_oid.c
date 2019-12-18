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
typedef  int uint64_t ;
struct asn_oid {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 scalar_t__ snmp_suboid_append (struct asn_oid*,int /*<<< orphan*/ ) ; 
 int strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static char *
snmp_cnt64_2asn_oid(char *str, struct asn_oid *oid)
{
	char *endptr;
	uint64_t v;
	int32_t saved_errno;

	saved_errno = errno;
	errno = 0;

	v = strtoull(str, &endptr, 10);

	if (errno != 0) {
		warn("Integer value %s not supported", str);
		errno = saved_errno;
		return (NULL);
	}
	errno = saved_errno;
	if (snmp_suboid_append(oid, (asn_subid_t) (v & 0xffffffff)) < 0)
		return (NULL);

	if (snmp_suboid_append(oid, (asn_subid_t) (v >> 32)) < 0)
		return (NULL);

	return (endptr);
}