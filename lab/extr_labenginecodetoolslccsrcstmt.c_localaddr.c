#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Tree ;
struct TYPE_4__ {int /*<<< orphan*/ * sym; } ;
struct TYPE_5__ {int const op; struct TYPE_5__** kids; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/ * Symbol ;

/* Variables and functions */
#define  ADDRF 135 
#define  ADDRL 134 
#define  ARG 133 
#define  ASGN 132 
#define  CALL 131 
#define  COND 130 
#define  INDIR 129 
#define  RIGHT 128 
 int /*<<< orphan*/  assert (int) ; 
 int generic (int const) ; 

__attribute__((used)) static Symbol localaddr(Tree p) {
	if (p == NULL)
		return NULL;
	switch (generic(p->op)) {
	case INDIR: case CALL: case ARG:
		return NULL;
	case ADDRL: case ADDRF:
		return p->u.sym;
	case RIGHT: case ASGN:
		if (p->kids[1])
			return localaddr(p->kids[1]);
		return localaddr(p->kids[0]);
	case COND: {
		Symbol q;
		assert(p->kids[1] && p->kids[1]->op == RIGHT);
		if ((q = localaddr(p->kids[1]->kids[0])) != NULL)
			return q;
		return localaddr(p->kids[1]->kids[1]);
		}
	default: {
		Symbol q;
		if (p->kids[0] && (q = localaddr(p->kids[0])) != NULL)
			return q;
		return localaddr(p->kids[1]);
		}
	}
}