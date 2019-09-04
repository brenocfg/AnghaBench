#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_19__ {int size; int /*<<< orphan*/  op; } ;

/* Variables and functions */
#define  F 131 
#define  I 130 
 int /*<<< orphan*/  INT ; 
#define  P 129 
#define  U 128 
 int /*<<< orphan*/  UNSIGNED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* chartype ; 
 TYPE_1__* doubletype ; 
 TYPE_1__* floattype ; 
 TYPE_1__* funcptype ; 
 TYPE_1__* inttype ; 
 TYPE_1__* longdouble ; 
 TYPE_1__* longlong ; 
 TYPE_1__* longtype ; 
 int optype (int) ; 
 TYPE_1__* shorttype ; 
 TYPE_1__* signedchar ; 
 TYPE_1__* unsignedchar ; 
 TYPE_1__* unsignedlong ; 
 TYPE_1__* unsignedlonglong ; 
 TYPE_1__* unsignedshort ; 
 TYPE_1__* unsignedtype ; 
 TYPE_1__* voidptype ; 

Type btot(int op, int size) {
#define xx(ty) if (size == (ty)->size) return ty;
	switch (optype(op)) {
	case F:
		xx(floattype);
		xx(doubletype);
		xx(longdouble);
		assert(0); return 0;
	case I:
		if (chartype->op == INT)
			xx(chartype);
		xx(signedchar);
		xx(shorttype);
		xx(inttype);
		xx(longtype);
		xx(longlong);
		assert(0); return 0;
	case U:
		if (chartype->op == UNSIGNED)
			xx(chartype);
		xx(unsignedchar);
		xx(unsignedshort);
		xx(unsignedtype);
		xx(unsignedlong);
		xx(unsignedlonglong);
		assert(0); return 0;
	case P:
		xx(voidptype);
		xx(funcptype);
		assert(0); return 0;
	}
#undef xx
	assert(0); return 0;
}