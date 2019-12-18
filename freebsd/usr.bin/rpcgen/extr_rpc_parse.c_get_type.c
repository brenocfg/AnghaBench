#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kind; char* str; } ;
typedef  TYPE_1__ token ;
typedef  int /*<<< orphan*/  defkind ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_PROGRAM ; 
 int /*<<< orphan*/  DEF_UNION ; 
#define  TOK_BOOL 144 
#define  TOK_CHAR 143 
#define  TOK_DOUBLE 142 
#define  TOK_ENUM 141 
#define  TOK_FLOAT 140 
#define  TOK_HYPER 139 
#define  TOK_IDENT 138 
#define  TOK_INT 137 
#define  TOK_LONG 136 
#define  TOK_OPAQUE 135 
#define  TOK_QUAD 134 
#define  TOK_SHORT 133 
#define  TOK_STRING 132 
#define  TOK_STRUCT 131 
#define  TOK_UNION 130 
#define  TOK_UNSIGNED 129 
#define  TOK_VOID 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  get_token (TYPE_1__*) ; 
 int /*<<< orphan*/  peekscan (int,TYPE_1__*) ; 
 int /*<<< orphan*/  scan (int const,TYPE_1__*) ; 
 int /*<<< orphan*/  unsigned_dec (char const**) ; 

__attribute__((used)) static void
get_type(const char **prefixp, const char **typep, defkind dkind)
{
	token tok;

	*prefixp = NULL;
	get_token(&tok);
	switch (tok.kind) {
	case TOK_IDENT:
		*typep = tok.str;
		break;
	case TOK_STRUCT:
	case TOK_ENUM:
	case TOK_UNION:
		*prefixp = tok.str;
		scan(TOK_IDENT, &tok);
		*typep = tok.str;
		break;
	case TOK_UNSIGNED:
		unsigned_dec(typep);
		break;
	case TOK_SHORT:
		*typep = "short";
		(void) peekscan(TOK_INT, &tok);
		break;
	case TOK_LONG:
		*typep = "long";
		(void) peekscan(TOK_INT, &tok);
		break;
	case TOK_HYPER:
		*typep = "int64_t";
		(void) peekscan(TOK_INT, &tok);
		break;

	case TOK_VOID:
		if (dkind != DEF_UNION && dkind != DEF_PROGRAM) {
			error("voids allowed only inside union and program definitions with one argument");
		}
		*typep = tok.str;
		break;
	case TOK_STRING:
	case TOK_OPAQUE:
	case TOK_CHAR:
	case TOK_INT:
	case TOK_FLOAT:
	case TOK_DOUBLE:
	case TOK_BOOL:
	case TOK_QUAD:
		*typep = tok.str;
		break;
	default:
		error("expected type specifier");
	}
}