#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  counter64; } ;
struct snmp_value {TYPE_1__ v; int /*<<< orphan*/  syntax; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_COUNTER64 ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_uint64(struct snmp_value *value, char *val)
{
	char *endptr;
	int32_t saved_errno;
	uint64_t v;

	saved_errno = errno;
	errno = 0;

	v = strtoull(val, &endptr, 10);

	if (errno != 0) {
		warnx("Value %s not supported", val);
		errno = saved_errno;
		return (-1);
	}

	value->syntax = SNMP_SYNTAX_COUNTER64;
	value->v.counter64 = v;
	errno = saved_errno;

	return (0);
}