#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * Type ;
typedef  TYPE_2__* Tree ;
struct TYPE_38__ {scalar_t__ scope; int /*<<< orphan*/  name; scalar_t__ generated; scalar_t__ computed; } ;
struct TYPE_37__ {int /*<<< orphan*/  type; TYPE_1__** kids; } ;
struct TYPE_36__ {int /*<<< orphan*/  type; } ;
struct TYPE_35__ {scalar_t__ returns; } ;
struct TYPE_34__ {TYPE_2__** kids; } ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  ASGN ; 
 int /*<<< orphan*/  AUTO ; 
 scalar_t__ B ; 
 scalar_t__ CALL ; 
 scalar_t__ PARAM ; 
 int /*<<< orphan*/  RET ; 
 scalar_t__ RIGHT ; 
 int /*<<< orphan*/  addlocal (TYPE_3__*) ; 
 int /*<<< orphan*/  apply (scalar_t__,TYPE_21__*,TYPE_2__*) ; 
 TYPE_2__* asgn (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* asgntree (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * assign (char*,TYPE_2__*) ; 
 TYPE_2__* cast (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_21__* cfunc ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_20__ events ; 
 char* freturn (int /*<<< orphan*/ ) ; 
 TYPE_3__* genident (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* idtree (TYPE_3__*) ; 
 scalar_t__ iscallb (TYPE_2__*) ; 
 int /*<<< orphan*/  isfloat (int /*<<< orphan*/ ) ; 
 scalar_t__ isptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  level ; 
 TYPE_3__* localaddr (TYPE_2__*) ; 
 scalar_t__ mkop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* pointer (TYPE_2__*) ; 
 int /*<<< orphan*/ * promote (int /*<<< orphan*/ ) ; 
 TYPE_3__* retv ; 
 TYPE_2__* rvalue (TYPE_2__*) ; 
 TYPE_2__* tree (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  walk (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char*,...) ; 

void retcode(Tree p) {
	Type ty;

	if (p == NULL) {
		if (events.returns)
			apply(events.returns, cfunc, NULL);
		return;
	}
	p = pointer(p);
	ty = assign(freturn(cfunc->type), p);
	if (ty == NULL) {
		error("illegal return type; found `%t' expected `%t'\n",
			p->type, freturn(cfunc->type));
		return;
	}
	p = cast(p, ty);
	if (retv)
		{
			if (iscallb(p))
				p = tree(RIGHT, p->type,
					tree(CALL+B, p->type,
						p->kids[0]->kids[0], idtree(retv)),
					rvalue(idtree(retv)));
			else
				p = asgntree(ASGN, rvalue(idtree(retv)), p);
			walk(p, 0, 0);
			if (events.returns)
				apply(events.returns, cfunc, rvalue(idtree(retv)));
			return;
		}
	if (events.returns)
		{
			Symbol t1 = genident(AUTO, p->type, level);
			addlocal(t1);
			walk(asgn(t1, p), 0, 0);
			apply(events.returns, cfunc, idtree(t1));
			p = idtree(t1);
		}
	if (!isfloat(p->type))
		p = cast(p, promote(p->type));
	if (isptr(p->type))
		{
			Symbol q = localaddr(p);
			if (q && (q->computed || q->generated))
				warning("pointer to a %s is an illegal return value\n",
					q->scope == PARAM ? "parameter" : "local");
			else if (q)
				warning("pointer to %s `%s' is an illegal return value\n",
					q->scope == PARAM ? "parameter" : "local", q->name);
		}
	walk(tree(mkop(RET,p->type), p->type, p, NULL), 0, 0);
}