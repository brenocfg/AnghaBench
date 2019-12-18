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
struct TYPE_2__ {int /*<<< orphan*/ * ipaddress; } ;
struct snmp_value {TYPE_1__ v; int /*<<< orphan*/  syntax; } ;
typedef  int int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_SYNTAX_IPADDRESS ; 

__attribute__((used)) static int32_t
add_ip_syntax(struct snmp_value *dst, struct snmp_value *src)
{
	int8_t i;

	dst->syntax = SNMP_SYNTAX_IPADDRESS;
	for (i = 0; i < 4; i++)
		dst->v.ipaddress[i] = src->v.ipaddress[i];

	return (1);
}