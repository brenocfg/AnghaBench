#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
typedef  TYPE_2__* Tree ;
struct TYPE_40__ {int /*<<< orphan*/  type; } ;
struct TYPE_39__ {TYPE_5__* type; } ;
struct TYPE_38__ {long size; TYPE_5__* type; } ;

/* Variables and functions */
 int DIV ; 
 int I ; 
 int /*<<< orphan*/  MUL ; 
 int P ; 
 int SUB ; 
 int U ; 
 TYPE_1__* binary (TYPE_5__*,TYPE_5__*) ; 
 TYPE_2__* cast (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* cnsttree (TYPE_1__*,long) ; 
 scalar_t__ compatible (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  error (char*,TYPE_5__*) ; 
 TYPE_1__* inttype ; 
 scalar_t__ isarith (TYPE_5__*) ; 
 int /*<<< orphan*/  isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ isint (TYPE_5__*) ; 
 scalar_t__ isptr (TYPE_5__*) ; 
 scalar_t__ isunsigned (TYPE_5__*) ; 
 TYPE_1__* longtype ; 
 TYPE_2__* multree (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* promote (TYPE_5__*) ; 
 TYPE_1__* signedptr ; 
 TYPE_2__* simplify (int,TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  typeerror (int,TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* unqual (TYPE_5__*) ; 
 TYPE_1__* unsignedptr ; 

__attribute__((used)) static Tree subtree(int op, Tree l, Tree r) {
	long n;
	Type ty = inttype;

	if (isarith(l->type) && isarith(r->type)) {
		ty = binary(l->type, r->type);
		l = cast(l, ty);
		r = cast(r, ty);		
	} else if (isptr(l->type) && !isfunc(l->type->type) && isint(r->type)) {
		ty = unqual(l->type);
		n = unqual(ty->type)->size;
		if (n == 0)
			error("unknown size for type `%t'\n", ty->type);
		r = cast(r, promote(r->type));
		if (n > 1)
			r = multree(MUL, cnsttree(signedptr, n), r);
		if (isunsigned(r->type))
			r = cast(r, unsignedptr);
		else
			r = cast(r, signedptr);
		return simplify(SUB+P, ty, l, r);
	} else if (compatible(l->type, r->type)) {
		ty = unqual(l->type);
		n = unqual(ty->type)->size;
		if (n == 0)
			error("unknown size for type `%t'\n", ty->type);
		l = simplify(SUB+U, unsignedptr,
			cast(l, unsignedptr), cast(r, unsignedptr));
		return simplify(DIV+I, longtype,
			cast(l, longtype), cnsttree(longtype, n));
	} else
		typeerror(op, l, r);
	return simplify(op, ty, l, r);
}