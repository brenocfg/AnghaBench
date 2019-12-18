#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; char* str; } ;
typedef  TYPE_1__ token ;
typedef  scalar_t__ defkind ;
struct TYPE_9__ {scalar_t__ rel; char* type; char* name; char* array_max; int /*<<< orphan*/ * prefix; } ;
typedef  TYPE_2__ declaration ;

/* Variables and functions */
 char* ARGNAME ; 
 scalar_t__ DEF_PROGRAM ; 
 void* REL_ALIAS ; 
 scalar_t__ REL_ARRAY ; 
 scalar_t__ REL_POINTER ; 
 int /*<<< orphan*/  TOK_IDENT ; 
 int /*<<< orphan*/  TOK_LANGLE ; 
 int /*<<< orphan*/  TOK_RANGLE ; 
 scalar_t__ TOK_RPAREN ; 
 int /*<<< orphan*/  TOK_STAR ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  get_type (int /*<<< orphan*/ **,char**,scalar_t__) ; 
 int /*<<< orphan*/  peek (TYPE_1__*) ; 
 scalar_t__ peekscan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scan_num (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ streq (char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
get_prog_declaration(declaration *dec, defkind dkind, int num)
{
	token tok;
	char name[10];		/* argument name */

	if (dkind == DEF_PROGRAM) {
		peek(&tok);
		if (tok.kind == TOK_RPAREN) { /* no arguments */
			dec->rel = REL_ALIAS;
			dec->type = "void";
			dec->prefix = NULL;
			dec->name = NULL;
			return;
		}
	}
	get_type(&dec->prefix, &dec->type, dkind);
	dec->rel = REL_ALIAS;
	if (peekscan(TOK_IDENT, &tok)) /* optional name of argument */
		strcpy(name, tok.str);
	else
		sprintf(name, "%s%d", ARGNAME, num);
	/* default name of argument */

	dec->name = (char *) xstrdup(name);
	if (streq(dec->type, "void")) {
		return;
	}

	if (streq(dec->type, "opaque")) {
		error("opaque -- illegal argument type");
	}
	if (peekscan(TOK_STAR, &tok)) {
		if (streq(dec->type, "string")) {
			error("pointer to string not allowed in program arguments");
		}
		dec->rel = REL_POINTER;
		if (peekscan(TOK_IDENT, &tok)) {
			/* optional name of argument */
			dec->name = xstrdup(tok.str);
		}
	}
	if (peekscan(TOK_LANGLE, &tok)) {
		if (!streq(dec->type, "string")) {
			error("arrays cannot be declared as arguments to procedures -- use typedef");
		}
		dec->rel = REL_ARRAY;
		if (peekscan(TOK_RANGLE, &tok)) {
			dec->array_max = "~0";
			/* unspecified size, use max */
		} else {
			scan_num(&tok);
			dec->array_max = tok.str;
			scan(TOK_RANGLE, &tok);
		}
	}
	if (streq(dec->type, "string")) {
		if (dec->rel != REL_ARRAY) {
			/*
			 * .x specifies just string as
			 * type of argument
			 * - make it string<>
			 */
			dec->rel = REL_ARRAY;
			dec->array_max = "~0"; /* unspecified size, use max */
		}
	}
}