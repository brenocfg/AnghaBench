#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_22__ {int oldstyle; TYPE_3__** proto; } ;
struct TYPE_23__ {TYPE_1__ f; } ;
struct TYPE_24__ {int op; int size; TYPE_2__ u; struct TYPE_24__* type; int /*<<< orphan*/  align; } ;
typedef  int /*<<< orphan*/ * List ;

/* Variables and functions */
#define  ARRAY 132 
#define  CONST 131 
#define  FUNCTION 130 
 int /*<<< orphan*/  PERM ; 
#define  POINTER 129 
#define  VOLATILE 128 
 int /*<<< orphan*/ * append (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* array (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* func (TYPE_3__*,TYPE_3__**,int) ; 
 int /*<<< orphan*/  isconst (TYPE_3__*) ; 
 int /*<<< orphan*/  isvolatile (TYPE_3__*) ; 
 TYPE_3__** ltov (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_3__* ptr (TYPE_3__*) ; 
 TYPE_3__* qual (int const,TYPE_3__*) ; 
 TYPE_3__* unqual (TYPE_3__*) ; 

Type compose(Type ty1, Type ty2) {
	if (ty1 == ty2)
		return ty1;
	assert(ty1->op == ty2->op);
	switch (ty1->op) {
	case POINTER:
		return ptr(compose(ty1->type, ty2->type));
	case CONST+VOLATILE:
		return qual(CONST, qual(VOLATILE,
			compose(ty1->type, ty2->type)));
	case CONST: case VOLATILE:
		return qual(ty1->op, compose(ty1->type, ty2->type));
	case ARRAY:    { Type ty = compose(ty1->type, ty2->type);
			 if (ty1->size && ((ty1->type->size && ty2->size == 0) || ty1->size == ty2->size))
			 	return array(ty, ty1->size/ty1->type->size, ty1->align);
			 if (ty2->size && ty2->type->size && ty1->size == 0)
			 	return array(ty, ty2->size/ty2->type->size, ty2->align);
			 return array(ty, 0, 0);    }
	case FUNCTION: { Type *p1  = ty1->u.f.proto, *p2 = ty2->u.f.proto;
			 Type ty   = compose(ty1->type, ty2->type);
			 List tlist = NULL;
			 if (p1 == NULL && p2 == NULL)
			 	return func(ty, NULL, 1);
			 if (p1 && p2 == NULL)
			 	return func(ty, p1, ty1->u.f.oldstyle);
			 if (p2 && p1 == NULL)
			 	return func(ty, p2, ty2->u.f.oldstyle);
			 for ( ; *p1 && *p2; p1++, p2++) {
			 	Type ty = compose(unqual(*p1), unqual(*p2));
			 	if (isconst(*p1)    || isconst(*p2))
			 		ty = qual(CONST, ty);
			 	if (isvolatile(*p1) || isvolatile(*p2))
			 		ty = qual(VOLATILE, ty);
			 	tlist = append(ty, tlist);
			 }
			 assert(*p1 == NULL && *p2 == NULL);
			 return func(ty, ltov(&tlist, PERM), 0); }
	}
	assert(0); return NULL;
}