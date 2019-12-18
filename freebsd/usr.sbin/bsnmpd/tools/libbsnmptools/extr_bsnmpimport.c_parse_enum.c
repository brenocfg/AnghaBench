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
struct enum_pairs {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int TOK_NUM ; 
 int TOK_STR ; 
 scalar_t__ enum_pair_insert (struct enum_pairs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gettoken (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  nexttok ; 
 int /*<<< orphan*/  val ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
parse_enum(struct snmp_toolinfo *snmptoolctx, int32_t *tok,
    struct enum_pairs *enums)
{
	while ((*tok = gettoken(snmptoolctx)) == TOK_STR) {
		if (enum_pair_insert(enums, val, nexttok) < 0)
			return (-1);
		if ((*tok = gettoken(snmptoolctx)) != TOK_NUM)
			break;
	}

	if (*tok != ')') {
		warnx("')' at end of enums");
		return (-1);
	}

	return (1);
}