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
struct TYPE_7__ {int op; int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  INT 130 
#define  POINTER 129 
#define  UNSIGNED 128 
 TYPE_1__* inttype ; 
 TYPE_1__* unsignedptr ; 
 TYPE_1__* unsignedtype ; 

__attribute__((used)) static Type super(Type ty) {
	switch (ty->op) {
	case INT:
		if (ty->size < inttype->size)
			return inttype;
		break;
	case UNSIGNED:
		if (ty->size < unsignedtype->size)
			return unsignedtype;
		break;
	case POINTER:
		return unsignedptr;
	}
	return ty;
}