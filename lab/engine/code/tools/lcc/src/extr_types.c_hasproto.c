#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_5__ {int /*<<< orphan*/  proto; } ;
struct TYPE_6__ {TYPE_1__ f; } ;
struct TYPE_7__ {int op; TYPE_2__ u; struct TYPE_7__* type; } ;

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

int hasproto(Type ty) {
	if (ty == 0)
		return 1;
	switch (ty->op) {
	case CONST: case VOLATILE: case CONST+VOLATILE: case POINTER:
	case ARRAY:
		return hasproto(ty->type);
	case FUNCTION:
		return hasproto(ty->type) && ty->u.f.proto;
	case STRUCT: case UNION:
	case VOID:   case FLOAT: case ENUM:  case INT: case UNSIGNED:
		return 1;
	}
	assert(0); return 0;
}