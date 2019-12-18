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
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;

/* Variables and functions */
 int TOK_STR ; 
 int gettoken (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  nexttok ; 
 int snmp_get_tc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
parse_subtype(struct snmp_toolinfo *snmptoolctx, int32_t *tok,
    enum snmp_tc *tc)
{
	if ((*tok = gettoken(snmptoolctx)) != TOK_STR) {
		warnx("subtype expected after '|'");
		return (-1);
	}

	*tc = snmp_get_tc(nexttok);
	*tok = gettoken(snmptoolctx);

	return (1);
}