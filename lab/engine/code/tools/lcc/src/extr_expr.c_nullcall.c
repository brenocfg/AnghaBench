#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
typedef  TYPE_4__* Tree ;
struct TYPE_25__ {int /*<<< orphan*/  type; } ;
struct TYPE_24__ {scalar_t__ align; scalar_t__ size; int /*<<< orphan*/  type; } ;
struct TYPE_22__ {int /*<<< orphan*/  loc; } ;
struct TYPE_23__ {TYPE_1__ c; } ;
struct TYPE_21__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  Symbol ;

/* Variables and functions */
 TYPE_3__* atop (TYPE_3__*) ; 
 int /*<<< orphan*/  cnsttree (int /*<<< orphan*/ ,long) ; 
 scalar_t__* file ; 
 int /*<<< orphan*/  idtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 scalar_t__ isarray (TYPE_3__*) ; 
 scalar_t__ lineno ; 
 TYPE_17__* mkstr (scalar_t__*) ; 
 int /*<<< orphan*/  pointer (int /*<<< orphan*/ ) ; 
 TYPE_4__* retype (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* unqual (int /*<<< orphan*/ ) ; 
 TYPE_4__* vcall (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  voidptype ; 

Tree nullcall(Type pty, Symbol f, Tree p, Tree e) {
	Type ty;

	if (isarray(pty))
		return retype(nullcall(atop(pty), f, p, e), pty);
	ty = unqual(unqual(p->type)->type);
	return vcall(f, pty,
		p, e,
		cnsttree(inttype, (long)ty->size),
		cnsttree(inttype, (long)ty->align),
		(file && *file ? pointer(idtree(mkstr(file)->u.c.loc)) : cnsttree(voidptype, NULL)), cnsttree(inttype, (long)lineno)		, NULL);
}