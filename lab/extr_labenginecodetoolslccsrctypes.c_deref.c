#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_9__ {TYPE_1__* type; } ;
struct TYPE_8__ {struct TYPE_8__* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ isenum (TYPE_1__*) ; 
 scalar_t__ isptr (TYPE_1__*) ; 
 TYPE_2__* unqual (TYPE_1__*) ; 

Type deref(Type ty) {
	if (isptr(ty))
		ty = ty->type;
	else
		error("type error: %s\n", "pointer expected");
	return isenum(ty) ? unqual(ty)->type : ty;
}