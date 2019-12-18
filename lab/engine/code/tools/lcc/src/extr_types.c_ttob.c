#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int op; int /*<<< orphan*/  size; struct TYPE_6__* type; } ;

/* Variables and functions */
#define  ARRAY 139 
#define  CONST 138 
#define  ENUM 137 
#define  FLOAT 136 
#define  FUNCTION 135 
#define  INT 134 
#define  POINTER 133 
#define  STRUCT 132 
#define  UNION 131 
#define  UNSIGNED 130 
#define  VOID 129 
#define  VOLATILE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* funcptype ; 
 TYPE_4__* inttype ; 
 int const sizeop (int /*<<< orphan*/ ) ; 
 TYPE_2__* voidptype ; 

int ttob(Type ty) {
	switch (ty->op) {
	case CONST: case VOLATILE: case CONST+VOLATILE:
		return ttob(ty->type);
	case VOID: case INT: case UNSIGNED: case FLOAT:
		return ty->op + sizeop(ty->size);
	case POINTER:
		return POINTER + sizeop(voidptype->size);
	case FUNCTION:
		return POINTER + sizeop(funcptype->size);
	case ARRAY: case STRUCT: case UNION:
		return STRUCT;
	case ENUM:
		return INT + sizeop(inttype->size);
	}
	assert(0); return INT;
}