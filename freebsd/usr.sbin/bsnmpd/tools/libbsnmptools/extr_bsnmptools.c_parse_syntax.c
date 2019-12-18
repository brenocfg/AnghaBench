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
typedef  size_t int32_t ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;
struct TYPE_2__ {int stx; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int SNMP_SYNTAX_NULL ; 
 size_t SNMP_SYNTAX_UNKNOWN ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* syntax_strings ; 

enum snmp_syntax
parse_syntax(char *str)
{
	int32_t i;

	for (i = 0; i < SNMP_SYNTAX_UNKNOWN; i++) {
		if (strncmp(syntax_strings[i].str, str,
		    strlen(syntax_strings[i].str)) == 0)
			return (syntax_strings[i].stx);
	}

	return (SNMP_SYNTAX_NULL);
}