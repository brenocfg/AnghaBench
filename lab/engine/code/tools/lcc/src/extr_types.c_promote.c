#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_9__ {int op; int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  ENUM 131 
#define  FLOAT 130 
#define  INT 129 
#define  UNSIGNED 128 
 TYPE_1__* doubletype ; 
 TYPE_1__* inttype ; 
 TYPE_1__* unqual (TYPE_1__*) ; 
 TYPE_1__* unsignedtype ; 

Type promote(Type ty) {
	ty = unqual(ty);
	switch (ty->op) {
	case ENUM:
		return inttype;
	case INT:
		if (ty->size < inttype->size)
			return inttype;
		break;
	case UNSIGNED:
		if (ty->size < inttype->size)
			return inttype;
		if (ty->size < unsignedtype->size)
			return unsignedtype;
		break;
	case FLOAT:
		if (ty->size < doubletype->size)
			return doubletype;
	}
	return ty;
}