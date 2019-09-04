#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_12__ {int oldstyle; TYPE_3__** proto; } ;
struct TYPE_13__ {TYPE_1__ f; } ;
struct TYPE_14__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCTION ; 
 int /*<<< orphan*/  error (char*,TYPE_3__*) ; 
 scalar_t__ isarray (TYPE_3__*) ; 
 scalar_t__ isfunc (TYPE_3__*) ; 
 TYPE_3__* type (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Type func(Type ty, Type *proto, int style) {
	if (ty && (isarray(ty) || isfunc(ty)))
		error("illegal return type `%t'\n", ty);
	ty = type(FUNCTION, ty, 0, 0, NULL);
	ty->u.f.proto = proto;
	ty->u.f.oldstyle = style;
	return ty;
}