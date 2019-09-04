#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_7__ {scalar_t__ op; scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ INT ; 
 scalar_t__ UNSIGNED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* inttype ; 
 TYPE_1__* longlong ; 
 TYPE_1__* longtype ; 

Type signedint(Type ty) {
	if (ty->op == INT)
		return ty;
	assert(ty->op == UNSIGNED);
#define xx(t) if (ty->size == t->size) return t
	xx(inttype);
	xx(longtype);
	xx(longlong);
#undef xx
	assert(0); return NULL;
}