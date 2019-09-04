#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int inst; } ;
struct TYPE_18__ {TYPE_4__** syms; TYPE_2__ x; } ;
struct TYPE_16__ {int /*<<< orphan*/  usecount; } ;
struct TYPE_17__ {TYPE_3__ x; int /*<<< orphan*/  name; scalar_t__ temporary; } ;
struct TYPE_14__ {short** _nts; scalar_t__* _isinstruction; int /*<<< orphan*/  (* _kids ) (TYPE_5__*,int,TYPE_5__**) ;} ;
struct TYPE_13__ {TYPE_1__ x; } ;
typedef  TYPE_5__* Node ;

/* Variables and functions */
 TYPE_12__* IR ; 
 size_t RX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int getrule (TYPE_5__*,int) ; 
 TYPE_5__* reuse (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,TYPE_5__**) ; 

__attribute__((used)) static void reduce(Node p, int nt) {
	int rulenum, i;
	short *nts;
	Node kids[10];

	p = reuse(p, nt);
	rulenum = getrule(p, nt);
	nts = IR->x._nts[rulenum];
	(*IR->x._kids)(p, rulenum, kids);
	for (i = 0; nts[i]; i++)
		reduce(kids[i], nts[i]);
	if (IR->x._isinstruction[rulenum]) {
		assert(p->x.inst == 0 || p->x.inst == nt);
		p->x.inst = nt;
		if (p->syms[RX] && p->syms[RX]->temporary) {
			debug(fprint(stderr, "(using %s)\n", p->syms[RX]->name));
			p->syms[RX]->x.usecount++;
		}
	}
}