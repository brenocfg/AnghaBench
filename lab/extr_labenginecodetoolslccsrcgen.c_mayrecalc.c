#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mayrecalc; } ;
struct TYPE_13__ {TYPE_1__ x; TYPE_5__** syms; } ;
struct TYPE_10__ {TYPE_2__* cse; } ;
struct TYPE_11__ {TYPE_3__ t; } ;
struct TYPE_12__ {TYPE_4__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  op; } ;
typedef  TYPE_6__* Node ;

/* Variables and functions */
 int ADDRF ; 
 int ADDRG ; 
 int ADDRL ; 
 int CNST ; 
 size_t RX ; 
 int /*<<< orphan*/  assert (int) ; 
 int generic (int /*<<< orphan*/ ) ; 

int mayrecalc(Node p) {
	int op;

	assert(p && p->syms[RX]);
	if (p->syms[RX]->u.t.cse == NULL)
		return 0;
	op = generic(p->syms[RX]->u.t.cse->op);
	if (op == CNST || op == ADDRF || op == ADDRG || op == ADDRL) {
		p->x.mayrecalc = 1;
		return 1;
	} else
		return 0;
}