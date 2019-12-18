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
struct snmp_toolinfo {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_NONE ; 
 int TOK_EOF ; 
#define  TOK_ERR 128 
 int /*<<< orphan*/  current_oid ; 
 int gettoken (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmp_import_object (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmp_import_update_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_suboid_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
snmp_import_tree(struct snmp_toolinfo *snmptoolctx, int32_t *tok)
{
	while (*tok != TOK_EOF) {
		switch (*tok) {
		    case TOK_ERR:
			return (-1);
		    case '(':
			if (snmp_import_object(snmptoolctx) < 0)
			    return (-1);
			break;
		    case ')':
			if (snmp_suboid_pop(&current_oid) < 0)
			    return (-1);
			(void) snmp_import_update_table(ENTRY_NONE, NULL);
			break;
		    default:
			/* Anything else here would be illegal. */
			return (-1);
		}
		*tok = gettoken(snmptoolctx);
	}

	return (0);
}