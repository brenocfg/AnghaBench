#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_21__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  src; } ;
struct TYPE_25__ {int /*<<< orphan*/  x; TYPE_8__** locals; } ;
struct TYPE_23__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  base; int /*<<< orphan*/  sym; } ;
struct TYPE_30__ {TYPE_8__* var; int /*<<< orphan*/  forest; TYPE_6__ point; TYPE_5__* begin; TYPE_2__ block; TYPE_1__ addr; } ;
struct TYPE_32__ {int kind; TYPE_7__ u; struct TYPE_32__* next; struct TYPE_32__* prev; } ;
struct TYPE_31__ {scalar_t__ sclass; scalar_t__ type; double ref; } ;
struct TYPE_26__ {int /*<<< orphan*/  x; } ;
struct TYPE_27__ {TYPE_3__ block; } ;
struct TYPE_28__ {TYPE_4__ u; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* local ) (TYPE_8__*) ;int /*<<< orphan*/  (* gen ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* blockend ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* blockbeg ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* address ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stabsym ) (TYPE_8__*) ;int /*<<< orphan*/  wants_dag; } ;
struct TYPE_22__ {TYPE_9__* next; } ;
typedef  TYPE_8__* Symbol ;
typedef  int /*<<< orphan*/  Coordinate ;
typedef  TYPE_9__* Code ;

/* Variables and functions */
#define  Address 136 
#define  Blockbeg 135 
#define  Blockend 134 
 int /*<<< orphan*/  CODE ; 
#define  Defpoint 133 
#define  Gen 132 
 TYPE_21__* IR ; 
#define  Jump 131 
#define  Label 130 
#define  Local 129 
#define  Switch 128 
 int /*<<< orphan*/  asgn (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ assignargs ; 
 TYPE_19__ codehead ; 
 TYPE_9__* codelist ; 
 scalar_t__ errcnt ; 
 int /*<<< orphan*/  fixup (int /*<<< orphan*/ ) ; 
 scalar_t__ glevel ; 
 int /*<<< orphan*/  idtree (TYPE_8__*) ; 
 int /*<<< orphan*/  prune (int /*<<< orphan*/ ) ; 
 int prunetemps ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_8__*) ; 
 int /*<<< orphan*/  swtoseg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gencode(Symbol caller[], Symbol callee[]) {
	Code cp;
	Coordinate save;

	if (prunetemps == -1)
		prunetemps = !IR->wants_dag;
	save = src;
	if (assignargs) {
		int i;
		Symbol p, q;
		cp = codehead.next->next;
		codelist = codehead.next;
		for (i = 0; (p = callee[i]) != NULL
		         && (q = caller[i]) != NULL; i++)
			if (p->sclass != q->sclass || p->type != q->type)
				walk(asgn(p, idtree(q)), 0, 0);
		codelist->next = cp;
		cp->prev = codelist;
	}
	if (glevel && IR->stabsym) {
		int i;
		Symbol p, q;
		for (i = 0; (p = callee[i]) != NULL
		         && (q = caller[i]) != NULL; i++) {
			(*IR->stabsym)(p);
			if (p->sclass != q->sclass || p->type != q->type)
				(*IR->stabsym)(q);
		}
		swtoseg(CODE);
	}
	cp = codehead.next;
	for ( ; errcnt <= 0 && cp; cp = cp->next)
		switch (cp->kind) {
		case Address:  (*IR->address)(cp->u.addr.sym, cp->u.addr.base,
			       	cp->u.addr.offset); break;
		case Blockbeg: {
			       	Symbol *p = cp->u.block.locals;
			       	(*IR->blockbeg)(&cp->u.block.x);
			       	for ( ; *p; p++)
			       		if ((*p)->ref != 0.0)
			       			(*IR->local)(*p);
			       		else if (glevel) (*IR->local)(*p);
			       }
 break;
		case Blockend: (*IR->blockend)(&cp->u.begin->u.block.x); break;
		case Defpoint: src = cp->u.point.src; break;
		case Gen: case Jump:
		case Label:    if (prunetemps)
			       	cp->u.forest = prune(cp->u.forest);
			       fixup(cp->u.forest);
			       cp->u.forest = (*IR->gen)(cp->u.forest); break;
		case Local:    (*IR->local)(cp->u.var); break;
		case Switch:   break;
		default: assert(0);
		}
	src = save;
}