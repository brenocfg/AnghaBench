#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
typedef  TYPE_1__* Tree ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_1__* cast (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 scalar_t__ isint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  promote (int /*<<< orphan*/ ) ; 
 TYPE_1__* simplify (int,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  typeerror (int,TYPE_1__*,TYPE_1__*) ; 

Tree shtree(int op, Tree l, Tree r) {
	Type ty = inttype;

	if (isint(l->type) && isint(r->type)) {
		ty = promote(l->type);
		l = cast(l, ty);
		r = cast(r, inttype);
	} else
		typeerror(op, l, r);
	return simplify(op, ty, l, r);
}