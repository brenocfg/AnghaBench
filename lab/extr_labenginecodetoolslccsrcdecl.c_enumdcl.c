#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_11__* Type ;
struct TYPE_34__ {TYPE_8__* sym; } ;
struct TYPE_32__ {int /*<<< orphan*/  idlist; } ;
struct TYPE_33__ {int defined; TYPE_7__ u; } ;
struct TYPE_31__ {long value; } ;
struct TYPE_30__ {TYPE_4__* sym; } ;
struct TYPE_26__ {long i; } ;
struct TYPE_27__ {TYPE_1__ max; } ;
struct TYPE_28__ {TYPE_2__ limits; } ;
struct TYPE_29__ {TYPE_3__ u; } ;
struct TYPE_25__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; TYPE_5__ u; } ;
struct TYPE_24__ {scalar_t__ scope; char src; } ;
struct TYPE_23__ {TYPE_11__* type; TYPE_6__ u; scalar_t__ sclass; int /*<<< orphan*/  src; } ;
struct TYPE_22__ {scalar_t__ op; TYPE_17__* type; TYPE_9__ u; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_12__* Symbol ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 int Aflag ; 
 scalar_t__ ENUM ; 
 int /*<<< orphan*/  FUNC ; 
 char ID ; 
#define  IF 128 
 scalar_t__ LOCAL ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  append (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 char gettok () ; 
 int /*<<< orphan*/  identifiers ; 
 TYPE_12__* install (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 long intexpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_17__* inttype ; 
 scalar_t__ level ; 
 TYPE_12__* lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltov (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_11__* newstruct (scalar_t__,char*) ; 
 int /*<<< orphan*/  src ; 
 char t ; 
 int /*<<< orphan*/  test (char,char*) ; 
 char* token ; 
 TYPE_14__* tsym ; 
 int /*<<< orphan*/  types ; 
 int /*<<< orphan*/  use (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 scalar_t__ xref ; 

Type enumdcl(void) {
	char *tag;
	Type ty;
	Symbol p = {0};
	Coordinate pos;

	t = gettok();
	pos = src;
	if (t == ID) {
		tag = token;
		t = gettok();
	} else
		tag = "";
	if (t == '{') {
		static char follow[] = { IF, 0 };
		int n = 0;
		long k = -1;
		List idlist = 0;
		ty = newstruct(ENUM, tag);
		t = gettok();
		if (t != ID)
			error("expecting an enumerator identifier\n");
		while (t == ID) {
			char *id = token;
			Coordinate s;
			if (tsym && tsym->scope == level)
				error("redeclaration of `%s' previously declared at %w\n",
					token, &tsym->src);
			s = src;
			t = gettok();
			if (t == '=') {
				t = gettok();
				k = intexpr(0, 0);
			} else {
				if (k == inttype->u.sym->u.limits.max.i)
					error("overflow in value for enumeration constant `%s'\n", id);
				k++;
			}
			p = install(id, &identifiers, level,  level < LOCAL ? PERM : FUNC);
			p->src = s;
			p->type = ty;
			p->sclass = ENUM;
			p->u.value = k;
			idlist = append(p, idlist);
			n++;
			if (Aflag >= 2 && n == 128)
				warning("more than 127 enumeration constants in `%t'\n", ty);
			if (t != ',')
				break;
			t = gettok();
			if (Aflag >= 2 && t == '}')
				warning("non-ANSI trailing comma in enumerator list\n");
		}
		test('}', follow);
		ty->type = inttype;
		ty->size = ty->type->size;
		ty->align = ty->type->align;
		ty->u.sym->u.idlist = ltov(&idlist, PERM);
		ty->u.sym->defined = 1;
	} else if ((p = lookup(tag, types)) != NULL && p->type->op == ENUM) {
		ty = p->type;
		if (t == ';')
			error("empty declaration\n");
	} else {
		error("unknown enumeration `%s'\n",  tag);
		ty = newstruct(ENUM, tag);
		ty->type = inttype;
	}
	if (*tag && xref)
		use(p, pos);
	return ty;
}