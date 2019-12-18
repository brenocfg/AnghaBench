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
struct enum_type {struct enum_pairs* snmp_enum; } ;
struct enum_pairs {int dummy; } ;
typedef  int int32_t ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;

/* Variables and functions */
 int SNMP_TC_OWN ; 
 int TOK_BITS ; 
 int TOK_DEFTYPE ; 
 int TOK_ENUM ; 
 int TOK_NUM ; 
 int /*<<< orphan*/  enum_pairs_free (struct enum_pairs*) ; 
 struct enum_pairs* enum_pairs_init () ; 
 int /*<<< orphan*/  free (struct enum_pairs*) ; 
 char gettoken (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  nexttok ; 
 scalar_t__ parse_enum (struct snmp_toolinfo*,int*,struct enum_pairs*) ; 
 scalar_t__ parse_subtype (struct snmp_toolinfo*,int*,int*) ; 
 struct enum_type* snmp_enumtc_lookup (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int val ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
parse_type(struct snmp_toolinfo *snmptoolctx, int32_t *tok,
    enum snmp_tc *tc, struct enum_pairs **snmp_enum)
{
	int32_t syntax, mem;

	syntax = val;
	*tc = 0;

	if (*tok == TOK_ENUM || *tok == TOK_BITS) {
		if (*snmp_enum == NULL) {
			if ((*snmp_enum = enum_pairs_init()) == NULL)
				return (-1);
			mem = 1;
			*tc = SNMP_TC_OWN;
		} else
			mem = 0;

		if (gettoken(snmptoolctx) != '(') {
			warnx("'(' expected after ENUM/BITS");
			return (-1);
		}

		if ((*tok = gettoken(snmptoolctx)) != TOK_NUM) {
			warnx("need value for ENUM//BITS");
			if (mem == 1) {
				free(*snmp_enum);
				*snmp_enum = NULL;
			}
			return (-1);
		}

		if (parse_enum(snmptoolctx, tok, *snmp_enum) < 0) {
			enum_pairs_free(*snmp_enum);
			*snmp_enum = NULL;
			return (-1);
		}

		*tok = gettoken(snmptoolctx);

	} else if (*tok == TOK_DEFTYPE) {
		struct enum_type *t;

		*tc = 0;
		t = snmp_enumtc_lookup(snmptoolctx, nexttok);
		if (t != NULL)
			*snmp_enum = t->snmp_enum;

		*tok = gettoken(snmptoolctx);

	} else {
		if ((*tok = gettoken(snmptoolctx)) == '|') {
			if (parse_subtype(snmptoolctx, tok, tc) < 0)
				return (-1);
		}
	}

	return (syntax);
}