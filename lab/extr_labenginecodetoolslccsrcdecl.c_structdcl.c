#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Type ;
struct TYPE_12__ {int defined; int /*<<< orphan*/  src; } ;
struct TYPE_11__ {scalar_t__ scope; TYPE_2__* type; } ;
struct TYPE_9__ {TYPE_4__* sym; } ;
struct TYPE_10__ {int op; TYPE_1__ u; } ;
typedef  TYPE_3__* Symbol ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 char ID ; 
#define  IF 128 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  fields (TYPE_2__*) ; 
 char gettok () ; 
 scalar_t__ istypename (char,int /*<<< orphan*/ ) ; 
 scalar_t__ level ; 
 TYPE_3__* lookup (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* newstruct (int,char*) ; 
 int /*<<< orphan*/  src ; 
 char t ; 
 int /*<<< orphan*/  test (char,char*) ; 
 char* token ; 
 int /*<<< orphan*/  tsym ; 
 int /*<<< orphan*/  types ; 
 int /*<<< orphan*/  use (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xref ; 

__attribute__((used)) static Type structdcl(int op) {
	char *tag;
	Type ty;
	Symbol p;
	Coordinate pos;

	t = gettok();
	pos = src;
	if (t == ID) {
		tag = token;
		t = gettok();
	} else
		tag = "";
	if (t == '{') {
		static char stop[] = { IF, ',', 0 };
		ty = newstruct(op, tag);
		ty->u.sym->src = pos;
		ty->u.sym->defined = 1;
		t = gettok();
		if (istypename(t, tsym))
			fields(ty);
		else
			error("invalid %k field declarations\n", op);
		test('}', stop);
	}
	else if (*tag && (p = lookup(tag, types)) != NULL
	&& p->type->op == op) {
		ty = p->type;
		if (t == ';' && p->scope < level)
			ty = newstruct(op, tag);
	}
	else {
		if (*tag == 0)
			error("missing %k tag\n", op);
		ty = newstruct(op, tag);
	}
	if (*tag && xref)
		use(ty->u.sym, pos);
	return ty;
}