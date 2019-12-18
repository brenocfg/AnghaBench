#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_7__ {int /*<<< orphan*/  (* defsymbol ) (TYPE_1__*) ;} ;
struct TYPE_6__ {int scope; int sclass; int generated; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 int GLOBAL ; 
 TYPE_5__* IR ; 
 int LOCAL ; 
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  genlabel (int) ; 
 int /*<<< orphan*/  stringd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

Symbol genident(int scls, Type ty, int lev) {
	Symbol p;

	NEW0(p, lev >= LOCAL ? FUNC : PERM);
	p->name = stringd(genlabel(1));
	p->scope = lev;
	p->sclass = scls;
	p->type = ty;
	p->generated = 1;
	if (lev == GLOBAL)
		(*IR->defsymbol)(p);
	return p;
}