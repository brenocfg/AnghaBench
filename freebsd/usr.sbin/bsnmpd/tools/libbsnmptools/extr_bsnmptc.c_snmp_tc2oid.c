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
struct asn_oid {int dummy; } ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {char* (* tc2oid ) (char*,struct asn_oid*) ;} ;

/* Variables and functions */
 int SNMP_UNKNOWN ; 
 char* stub1 (char*,struct asn_oid*) ; 
 TYPE_1__* text_convs ; 

char *
snmp_tc2oid(enum snmp_tc tc, char *str, struct asn_oid *oid)
{
	if (tc > SNMP_UNKNOWN)
		tc = SNMP_UNKNOWN;

	return (text_convs[tc].tc2oid(str, oid));
}