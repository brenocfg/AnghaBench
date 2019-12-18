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
struct TYPE_12__ {TYPE_3__** proto; } ;
struct TYPE_13__ {TYPE_1__ f; } ;
struct TYPE_14__ {int op; struct TYPE_14__* type; TYPE_2__ u; int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  ARRAY 138 
#define  CONST 137 
#define  ENUM 136 
#define  FLOAT 135 
#define  FUNCTION 134 
#define  INT 133 
#define  POINTER 132 
#define  STRUCT 131 
#define  UNION 130 
#define  UNSIGNED 129 
#define  VOLATILE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isenum (TYPE_3__*) ; 
 TYPE_3__* promote (TYPE_3__*) ; 
 TYPE_3__* unqual (TYPE_3__*) ; 
 int /*<<< orphan*/  variadic (TYPE_3__*) ; 

int eqtype(Type ty1, Type ty2, int ret) {
	if (ty1 == ty2)
		return 1;
	if (ty1->op != ty2->op)
		return 0;
	switch (ty1->op) {
	case ENUM: case UNION: case STRUCT:
	case UNSIGNED: case INT: case FLOAT:
		return 0;
	case POINTER:  return eqtype(ty1->type, ty2->type, 1);
	case VOLATILE: case CONST+VOLATILE:
	case CONST:    return eqtype(ty1->type, ty2->type, 1);
	case ARRAY:    if (eqtype(ty1->type, ty2->type, 1)) {
		       	if (ty1->size == ty2->size)
		       		return 1;
		       	if (ty1->size == 0 || ty2->size == 0)
		       		return ret;
		       }
		       return 0;
	case FUNCTION: if (eqtype(ty1->type, ty2->type, 1)) {
		       	Type *p1 = ty1->u.f.proto, *p2 = ty2->u.f.proto;
		       	if (p1 == p2)
		       		return 1;
		       	if (p1 && p2) {
		       		for ( ; *p1 && *p2; p1++, p2++)
					if (eqtype(unqual(*p1), unqual(*p2), 1) == 0)
						return 0;
				if (*p1 == NULL && *p2 == NULL)
					return 1;
		       	} else {
		       		if (variadic(p1 ? ty1 : ty2))
					return 0;
				if (p1 == NULL)
					p1 = p2;
				for ( ; *p1; p1++) {
					Type ty = unqual(*p1);
					if (promote(ty) != (isenum(ty) ? ty->type : ty))
						return 0;
				}
				return 1;
		       	}
		       }
		       return 0;
	}
	assert(0); return 0;
}