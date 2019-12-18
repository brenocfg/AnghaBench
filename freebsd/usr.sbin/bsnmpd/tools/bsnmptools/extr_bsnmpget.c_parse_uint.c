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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  uint32; } ;
struct snmp_value {TYPE_1__ v; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static int32_t
parse_uint(struct snmp_value *value, char *val)
{
	char *endptr;
	uint32_t v = 0;
	int32_t saved_errno;

	saved_errno = errno;
	errno = 0;

	v = strtoul(val, &endptr, 10);

	if (errno != 0) {
		warn("Value %s not supported", val);
		errno = saved_errno;
		return (-1);
	}

	value->v.uint32 = v;
	errno = saved_errno;

	return (0);
}