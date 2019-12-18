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
 int /*<<< orphan*/  binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cast (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 scalar_t__ isarith (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkop (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* simplify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  typeerror (int,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  unsignedptr ; 
 int /*<<< orphan*/  unsignedtype ; 

__attribute__((used)) static Tree cmptree(int op, Tree l, Tree r) {
	Type ty;

	if (isarith(l->type) && isarith(r->type)) {
		ty = binary(l->type, r->type);
		l = cast(l, ty);
		r = cast(r, ty);
	} else if (compatible(l->type, r->type)) {
		ty = unsignedptr;
		l = cast(l, ty);
		r = cast(r, ty);
	} else {
		ty = unsignedtype;
		typeerror(op, l, r);
	}
	return simplify(mkop(op,ty), inttype, l, r);
}