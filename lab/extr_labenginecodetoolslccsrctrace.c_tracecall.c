#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  size; } ;
struct TYPE_12__ {TYPE_3__** callee; } ;
struct TYPE_13__ {TYPE_1__ f; } ;
struct TYPE_14__ {char* name; TYPE_4__* type; TYPE_2__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* space ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO ; 
 int /*<<< orphan*/  BSS ; 
 int /*<<< orphan*/  GLOBAL ; 
 int /*<<< orphan*/  INCR ; 
 TYPE_10__* IR ; 
 int /*<<< orphan*/  STATIC ; 
 int /*<<< orphan*/  addlocal (void*) ; 
 int /*<<< orphan*/  appendstr (char*) ; 
 int /*<<< orphan*/  asgn (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consttree (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defglobal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* frameno ; 
 void* genident (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idtree (TYPE_3__*) ; 
 int /*<<< orphan*/  incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 int /*<<< orphan*/  level ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracefinis (TYPE_3__*) ; 
 int /*<<< orphan*/  tracevalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ variadic (TYPE_4__*) ; 

__attribute__((used)) static void tracecall(Symbol printer, Symbol f) {
	int i;
	Symbol counter = genident(STATIC, inttype, GLOBAL);

	defglobal(counter, BSS);
	(*IR->space)(counter->type->size);
	frameno = genident(AUTO, inttype, level);
	addlocal(frameno);
	appendstr(f->name); appendstr("#");
	tracevalue(asgn(frameno, incr(INCR, idtree(counter), consttree(1, inttype))), 0);
	appendstr("(");
	for (i = 0; f->u.f.callee[i]; i++) {
		if (i)
			appendstr(",");
		appendstr(f->u.f.callee[i]->name); appendstr("=");
		tracevalue(idtree(f->u.f.callee[i]), 0);
	}
	if (variadic(f->type))
		appendstr(",...");
	appendstr(") called\n");
	tracefinis(printer);
}