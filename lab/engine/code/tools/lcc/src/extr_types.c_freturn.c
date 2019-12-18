#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_6__ {struct TYPE_6__* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*) ; 
 TYPE_1__* inttype ; 
 scalar_t__ isfunc (TYPE_1__*) ; 

Type freturn(Type ty) {
	if (isfunc(ty))
		return ty->type;
	error("type error: %s\n", "function expected");
	return inttype;
}