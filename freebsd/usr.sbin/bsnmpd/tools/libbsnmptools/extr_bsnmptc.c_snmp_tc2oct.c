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
struct snmp_value {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc2oct ) (struct snmp_value*,char*) ;} ;

/* Variables and functions */
 int SNMP_UNKNOWN ; 
 int /*<<< orphan*/  stub1 (struct snmp_value*,char*) ; 
 TYPE_1__* text_convs ; 

int32_t
snmp_tc2oct(enum snmp_tc tc, struct snmp_value *value, char *string)
{
	if (tc > SNMP_UNKNOWN)
		tc = SNMP_UNKNOWN;

	return (text_convs[tc].tc2oct(value, string));
}