#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_16__ {int /*<<< orphan*/  oldstyle; int /*<<< orphan*/  proto; } ;
struct TYPE_17__ {TYPE_1__ f; } ;
struct TYPE_18__ {int op; int size; TYPE_2__ u; struct TYPE_18__* type; } ;
typedef  int /*<<< orphan*/  Symbol ;

/* Variables and functions */
#define  ARRAY 132 
 int Aflag ; 
#define  CONST 131 
#define  FUNCTION 130 
#define  POINTER 129 
#define  VOLATILE 128 
 TYPE_3__* array (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* dclr1 (char**,int /*<<< orphan*/ **,int) ; 
 TYPE_3__* func (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ptr (TYPE_3__*) ; 
 TYPE_3__* qual (int,TYPE_3__*) ; 
 int /*<<< orphan*/  warning (char*,TYPE_3__*) ; 

__attribute__((used)) static Type dclr(Type basety, char **id, Symbol **params, int abstract) {
	Type ty = dclr1(id, params, abstract);

	for ( ; ty; ty = ty->type)
		switch (ty->op) {
		case POINTER:
			basety = ptr(basety);
			break;
		case FUNCTION:
			basety = func(basety, ty->u.f.proto,
				ty->u.f.oldstyle);
			break;
		case ARRAY:
			basety = array(basety, ty->size, 0);
			break;
		case CONST: case VOLATILE:
			basety = qual(ty->op, basety);
			break;
		default: assert(0);
		}
	if (Aflag >= 2 && basety->size > 32767)
		warning("more than 32767 bytes in `%t'\n", basety);
	return basety;
}