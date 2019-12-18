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
struct snmp_value {int /*<<< orphan*/  syntax; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_GAUGE ; 
 scalar_t__ parse_uint (struct snmp_value*,char*) ; 

__attribute__((used)) static int32_t
parse_gauge(struct snmp_value *value, char *val)
{
	if (parse_uint(value, val) < 0)
		return (-1);

	value->syntax = SNMP_SYNTAX_GAUGE;
	return (0);
}