#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
typedef  TYPE_2__* Tree ;
struct TYPE_21__ {TYPE_1__* type; } ;
struct TYPE_20__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_2__* cast (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* cmptree (int,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ eqtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inttype ; 
 int /*<<< orphan*/  isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ isnullptr (TYPE_2__*) ; 
 scalar_t__ isptr (TYPE_1__*) ; 
 scalar_t__ isvoidptr (TYPE_1__*) ; 
 int /*<<< orphan*/  mkop (int,TYPE_1__*) ; 
 TYPE_2__* simplify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  unqual (int /*<<< orphan*/ ) ; 
 TYPE_1__* unsignedptr ; 

Tree eqtree(int op, Tree l, Tree r) {
	Type xty = l->type, yty = r->type;

	if ((isptr(xty) && isnullptr(r))
	||  (isptr(xty) && !isfunc(xty->type) && isvoidptr(yty))
	||  (isptr(xty) && isptr(yty)
	    && eqtype(unqual(xty->type), unqual(yty->type), 1))) {
		Type ty = unsignedptr;
		l = cast(l, ty);
		r = cast(r, ty);
		return simplify(mkop(op,ty), inttype, l, r);
	}
	if ((isptr(yty) && isnullptr(l))
	||  (isptr(yty) && !isfunc(yty->type) && isvoidptr(xty)))
		return eqtree(op, r, l);
	return cmptree(op, l, r);
}