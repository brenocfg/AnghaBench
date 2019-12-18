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
struct snmp_toolinfo {int dummy; } ;
struct enum_type {int is_enum; int is_bits; int /*<<< orphan*/  snmp_enum; int /*<<< orphan*/  syntax; } ;
typedef  char int32_t ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 char TOK_BITS ; 
 char TOK_ENUM ; 
 char TOK_FILENAME ; 
 char TOK_INCLUDE ; 
 char TOK_STR ; 
 char TOK_TYPEDEF ; 
 int add_filename (struct snmp_toolinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char gettoken (struct snmp_toolinfo*) ; 
 TYPE_1__* input ; 
 int /*<<< orphan*/  input_fopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexttok ; 
 int /*<<< orphan*/  parse_type (struct snmp_toolinfo*,char*,int*,int /*<<< orphan*/ *) ; 
 struct enum_type* snmp_enumtc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_enumtc_insert (struct snmp_toolinfo*,struct enum_type*) ; 
 char snmp_import_tree (struct snmp_toolinfo*,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
snmp_import_top(struct snmp_toolinfo *snmptoolctx, int32_t *tok)
{
	enum snmp_tc tc;
	struct enum_type *t;

	if (*tok == '(')
		return (snmp_import_tree(snmptoolctx, tok));

	if (*tok == TOK_TYPEDEF) {
		if ((*tok = gettoken(snmptoolctx)) != TOK_STR) {
			warnx("type name expected after typedef - %s",
			    input->fname);
			return (-1);
		}

		t = snmp_enumtc_init(nexttok);

		*tok = gettoken(snmptoolctx);
		t->is_enum = (*tok == TOK_ENUM);
		t->is_bits = (*tok == TOK_BITS);
		t->syntax = parse_type(snmptoolctx, tok, &tc, &(t->snmp_enum));
		snmp_enumtc_insert(snmptoolctx, t);

		return (1);
	}

	if (*tok == TOK_INCLUDE) {
		int i;

		*tok = gettoken(snmptoolctx);
		if (*tok != TOK_FILENAME) {
			warnx("filename expected in include directive - %s",
			    nexttok);
			return (-1);
		}

		if (( i = add_filename(snmptoolctx, nexttok, NULL, 1)) == 0) {
			*tok = gettoken(snmptoolctx);
			return (1);
		}

		if (i == -1)
			return (-1);

		input_fopen(nexttok);
		*tok = gettoken(snmptoolctx);
		return (1);
	}

	warnx("'(' or 'typedef' expected - %s", nexttok);
	return (-1);
}