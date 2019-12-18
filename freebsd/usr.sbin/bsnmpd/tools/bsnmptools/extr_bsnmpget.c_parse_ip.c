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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__* ipaddress; } ;
struct snmp_value {int /*<<< orphan*/  syntax; TYPE_1__ v; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_IPADDRESS ; 
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static int32_t
parse_ip(struct snmp_value * value, char * val)
{
	char *endptr, *str;
	int32_t i;
	uint32_t v;

	str = val;
	for (i = 0; i < 4; i++) {
		v = strtoul(str, &endptr, 10);
		if (v > 0xff)
			return (-1);
		if (*endptr != '.' && *endptr != '\0' && i != 3)
			break;
		str = endptr + 1;
		value->v.ipaddress[i] = (uint8_t) v;
	}
	value->syntax = SNMP_SYNTAX_IPADDRESS;

	return (0);
}