#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {struct TYPE_20__* link; } ;
struct TYPE_16__ {TYPE_3__* cse; } ;
struct TYPE_17__ {TYPE_1__ t; } ;
struct TYPE_19__ {int ref; TYPE_2__ u; int /*<<< orphan*/  defined; } ;
struct TYPE_18__ {int count; scalar_t__ op; TYPE_8__** syms; struct TYPE_18__** kids; } ;
typedef  TYPE_3__* Node ;

/* Variables and functions */
 scalar_t__ ADDRF ; 
 scalar_t__ ADDRL ; 
 scalar_t__ B ; 
 scalar_t__ INDIR ; 
 scalar_t__ P ; 
 int /*<<< orphan*/  REGISTER ; 
 TYPE_9__* asgnnode (TYPE_8__*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btot (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ iscall (scalar_t__) ; 
 TYPE_3__* newnode (scalar_t__,TYPE_3__*,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  opsize (scalar_t__) ; 
 scalar_t__ specific (scalar_t__) ; 
 TYPE_9__** tail ; 
 TYPE_8__* temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* tmpnode (TYPE_3__*) ; 

__attribute__((used)) static Node visit(Node p, int listed) {
	if (p) {
		if (p->syms[2])
			p = tmpnode(p);
		else if ((p->count <= 1 && !iscall(p->op))
		||       (p->count == 0 &&  iscall(p->op))) {
			p->kids[0] = visit(p->kids[0], 0);
			p->kids[1] = visit(p->kids[1], 0);
		}

		else if (specific(p->op) == ADDRL+P || specific(p->op) == ADDRF+P) {
			assert(!listed);
			p = newnode(p->op, NULL, NULL, p->syms[0]);
			p->count = 1;
		}
		else if (p->op == INDIR+B) {
			p = newnode(p->op, p->kids[0], NULL, NULL);
			p->count = 1;
			p->kids[0] = visit(p->kids[0], 0);
			p->kids[1] = visit(p->kids[1], 0);
		}
		else {
			p->kids[0] = visit(p->kids[0], 0);
			p->kids[1] = visit(p->kids[1], 0);
			p->syms[2] = temporary(REGISTER, btot(p->op, opsize(p->op)));
			assert(!p->syms[2]->defined);
			p->syms[2]->ref = 1;
			p->syms[2]->u.t.cse = p;

			*tail = asgnnode(p->syms[2], p);
			tail = &(*tail)->link;
			if (!listed)
				p = tmpnode(p);
		};
	}
	return p;
}