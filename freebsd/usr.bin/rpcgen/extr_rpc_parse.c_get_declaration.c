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
typedef  int /*<<< orphan*/  defkind ;
struct TYPE_9__ {scalar_t__ rel; char* name; char* array_max; int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
typedef  TYPE_2__ declaration ;

/* Variables and functions */
 scalar_t__ REL_ALIAS ; 
 scalar_t__ REL_ARRAY ; 
 scalar_t__ REL_POINTER ; 
 scalar_t__ REL_VECTOR ; 
 int /*<<< orphan*/  TOK_IDENT ; 
 int /*<<< orphan*/  TOK_LANGLE ; 
 int /*<<< orphan*/  TOK_LBRACKET ; 
 int /*<<< orphan*/  TOK_RANGLE ; 
 int /*<<< orphan*/  TOK_RBRACKET ; 
 scalar_t__ TOK_STAR ; 
 int /*<<< orphan*/  check_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  get_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ peekscan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scan (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scan2 (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scan_num (TYPE_1__*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
get_declaration(declaration *dec, defkind dkind)
{
	token tok;

	get_type(&dec->prefix, &dec->type, dkind);
	dec->rel = REL_ALIAS;
	if (streq(dec->type, "void")) {
		return;
	}

	check_type_name(dec->type, 0);
	scan2(TOK_STAR, TOK_IDENT, &tok);
	if (tok.kind == TOK_STAR) {
		dec->rel = REL_POINTER;
		scan(TOK_IDENT, &tok);
	}
	dec->name = tok.str;
	if (peekscan(TOK_LBRACKET, &tok)) {
		if (dec->rel == REL_POINTER) {
			error("no array-of-pointer declarations -- use typedef");
		}
		dec->rel = REL_VECTOR;
		scan_num(&tok);
		dec->array_max = tok.str;
		scan(TOK_RBRACKET, &tok);
	} else if (peekscan(TOK_LANGLE, &tok)) {
		if (dec->rel == REL_POINTER) {
			error("no array-of-pointer declarations -- use typedef");
		}
		dec->rel = REL_ARRAY;
		if (peekscan(TOK_RANGLE, &tok)) {
			dec->array_max = "~0";	/* unspecified size, use max */
		} else {
			scan_num(&tok);
			dec->array_max = tok.str;
			scan(TOK_RANGLE, &tok);
		}
	}
	if (streq(dec->type, "opaque")) {
		if (dec->rel != REL_ARRAY && dec->rel != REL_VECTOR) {
			error("array declaration expected");
		}
	} else if (streq(dec->type, "string")) {
		if (dec->rel != REL_ARRAY) {
			error("variable-length array declaration expected");
		}
	}
}