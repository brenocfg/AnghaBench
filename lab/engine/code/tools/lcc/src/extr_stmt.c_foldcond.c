#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_9__ {int i; } ;
struct TYPE_10__ {scalar_t__ sym; TYPE_1__ v; } ;
struct TYPE_11__ {scalar_t__ op; TYPE_2__ u; struct TYPE_11__** kids; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ Symbol ;

/* Variables and functions */
 int ASGN ; 
 int CNST ; 
 int EQ ; 
 int GE ; 
 int GT ; 
 int I ; 
 int INDIR ; 
 int LE ; 
 int LT ; 
 int NE ; 
 int generic (scalar_t__) ; 
 scalar_t__ isaddrop (scalar_t__) ; 
 TYPE_3__* simplify (int,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int foldcond(Tree e1, Tree e2) {
	int op = generic(e2->op);
	Symbol v;

	if (e1 == 0 || e2 == 0)
		return 0;
	if (generic(e1->op) == ASGN && isaddrop(e1->kids[0]->op)
	&& generic(e1->kids[1]->op) == CNST) {
		v = e1->kids[0]->u.sym;
		e1 = e1->kids[1];
	} else
		return 0;
	if ((op==LE || op==LT || op==EQ || op==NE || op==GT || op==GE)
	&& generic(e2->kids[0]->op) == INDIR
	&& e2->kids[0]->kids[0]->u.sym == v
	&& e2->kids[1]->op == e1->op) {
		e1 = simplify(op, e2->type, e1, e2->kids[1]);
		if (e1->op == CNST+I)
			return e1->u.v.i;
	}
	return 0;
}