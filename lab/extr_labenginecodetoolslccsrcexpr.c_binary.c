#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_14__ {scalar_t__ size; } ;

/* Variables and functions */
 TYPE_1__* doubletype ; 
 TYPE_1__* floattype ; 
 TYPE_1__* inttype ; 
 TYPE_1__* longdouble ; 
 TYPE_1__* longlong ; 
 TYPE_1__* longtype ; 
 TYPE_1__* unsignedlong ; 
 TYPE_1__* unsignedlonglong ; 
 TYPE_1__* unsignedtype ; 

Type binary(Type xty, Type yty) {
#define xx(t) if (xty == t || yty == t) return t
	xx(longdouble);
	xx(doubletype);
	xx(floattype);
	xx(unsignedlonglong);
	xx(longlong);
	xx(unsignedlong);
	if ((xty == longtype     && yty == unsignedtype)
	||  (xty == unsignedtype && yty == longtype)) {
		if (longtype->size > unsignedtype->size)
			return longtype;
		else
			return unsignedlong;
	}
	xx(longtype);
	xx(unsignedtype);
	return inttype;
#undef xx
}