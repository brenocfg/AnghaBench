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
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {int tc; int /*<<< orphan*/  tc_str; } ;

/* Variables and functions */
 int SNMP_STRING ; 
 int SNMP_UNKNOWN ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* text_convs ; 

enum snmp_tc
snmp_get_tc(char *str)
{
	int i;
	for (i = 0; i < SNMP_UNKNOWN; i++) {
		if (!strncmp(text_convs[i].tc_str, str,
		    strlen(text_convs[i].tc_str)))
			return (text_convs[i].tc);
	}

	return (SNMP_STRING);
}