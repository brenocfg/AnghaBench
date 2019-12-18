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
typedef  char* uint64_t ;
struct snmp_toolinfo {int dummy; } ;
struct TYPE_2__ {char* str; } ;

/* Variables and functions */
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 scalar_t__ OUTPUT_VERBOSE ; 
 size_t SNMP_SYNTAX_COUNTER64 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__* syntax_strings ; 

__attribute__((used)) static void
snmp_output_counter64(struct snmp_toolinfo *snmptoolctx, uint64_t counter64)
{
	if (GET_OUTPUT(snmptoolctx) == OUTPUT_VERBOSE)
		fprintf(stdout, "%s : ",
		    syntax_strings[SNMP_SYNTAX_COUNTER64].str);

	fprintf(stdout,"%ju", counter64);
}