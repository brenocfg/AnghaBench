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
struct TYPE_5__ {void** syms; TYPE_1__** kids; int /*<<< orphan*/  op; struct TYPE_5__* link; } ;
struct TYPE_4__ {void** syms; int /*<<< orphan*/  op; } ;
typedef  TYPE_2__* Node ;

/* Variables and functions */
 scalar_t__ ADDRG ; 
#define  EQ 135 
#define  GE 134 
#define  GT 133 
#define  JUMP 132 
#define  LABEL 131 
#define  LE 130 
#define  LT 129 
#define  NE 128 
 scalar_t__ P ; 
 int /*<<< orphan*/  assert (int) ; 
 void* equated (void*) ; 
 int generic (int /*<<< orphan*/ ) ; 
 scalar_t__ specific (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixup(Node p) {
	for ( ; p; p = p->link)
		switch (generic(p->op)) {
		case JUMP:
			if (specific(p->kids[0]->op) == ADDRG+P)
				p->kids[0]->syms[0] =
					equated(p->kids[0]->syms[0]);
			break;
		case LABEL: assert(p->syms[0] == equated(p->syms[0])); break;
		case EQ: case GE: case GT: case LE: case LT: case NE:
			assert(p->syms[0]);
			p->syms[0] = equated(p->syms[0]);
		}
}