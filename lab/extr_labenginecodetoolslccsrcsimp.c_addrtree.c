#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* Type ;
typedef  TYPE_5__* Tree ;
struct TYPE_21__ {long offset; TYPE_6__* base; TYPE_6__* sym; } ;
struct TYPE_23__ {TYPE_1__ addr; } ;
struct TYPE_28__ {TYPE_2__ u; } ;
struct TYPE_27__ {scalar_t__ scope; scalar_t__ sclass; int computed; int defined; int ref; int /*<<< orphan*/  addressed; int /*<<< orphan*/  generated; int /*<<< orphan*/  temporary; TYPE_4__* type; int /*<<< orphan*/  name; } ;
struct TYPE_24__ {TYPE_6__* sym; } ;
struct TYPE_26__ {TYPE_3__ u; int /*<<< orphan*/  op; } ;
struct TYPE_25__ {struct TYPE_25__* type; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* address ) (TYPE_6__*,TYPE_6__*,long) ;} ;
typedef  TYPE_6__* Symbol ;
typedef  TYPE_7__* Code ;

/* Variables and functions */
 scalar_t__ AUTO ; 
 int /*<<< orphan*/  Address ; 
 scalar_t__ EXTERN ; 
 int /*<<< orphan*/  FUNC ; 
 scalar_t__ GLOBAL ; 
 TYPE_20__* IR ; 
 int /*<<< orphan*/  NEW0 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 scalar_t__ STATIC ; 
 int /*<<< orphan*/  addlocal (TYPE_6__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlabel (int) ; 
 scalar_t__ isarray (TYPE_4__*) ; 
 scalar_t__ isptr (TYPE_4__*) ; 
 int /*<<< orphan*/  stringd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_6__*,long) ; 
 TYPE_5__* tree (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Tree addrtree(Tree e, long n, Type ty) {
	Symbol p = e->u.sym, q;

	if (p->scope  == GLOBAL
	||  p->sclass == STATIC || p->sclass == EXTERN)
		NEW0(q, PERM);
	else
		NEW0(q, FUNC);
	q->name = stringd(genlabel(1));
	q->sclass = p->sclass;
	q->scope = p->scope;
	assert(isptr(ty) || isarray(ty));
	q->type = isptr(ty) ? ty->type : ty;
	q->temporary = p->temporary;
	q->generated = p->generated;
	q->addressed = p->addressed;
	q->computed = 1;
	q->defined = 1;
	q->ref = 1;
	if (p->scope  == GLOBAL
	||  p->sclass == STATIC || p->sclass == EXTERN) {
		if (p->sclass == AUTO)
			q->sclass = STATIC;
		(*IR->address)(q, p, n);
	} else {
		Code cp;
		addlocal(p);
		cp = code(Address);
		cp->u.addr.sym = q;
		cp->u.addr.base = p;
		cp->u.addr.offset = n;
	}
	e = tree(e->op, ty, NULL, NULL);
	e->u.sym = q;
	return e;
}