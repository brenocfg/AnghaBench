#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ d; } ;
struct TYPE_17__ {TYPE_1__ v; } ;
struct TYPE_18__ {TYPE_2__ c; } ;
struct TYPE_24__ {TYPE_11__* type; TYPE_3__ u; } ;
struct TYPE_23__ {TYPE_7__* sym; } ;
struct TYPE_19__ {scalar_t__ d; } ;
struct TYPE_20__ {TYPE_4__ max; } ;
struct TYPE_21__ {TYPE_5__ limits; } ;
struct TYPE_22__ {TYPE_6__ u; } ;
struct TYPE_15__ {TYPE_8__ u; } ;
typedef  TYPE_9__* Symbol ;

/* Variables and functions */
 int DIGIT ; 
 scalar_t__ ERANGE ; 
 char* cp ; 
 TYPE_11__* doubletype ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 TYPE_11__* floattype ; 
 TYPE_11__* longdouble ; 
 int* map ; 
 int /*<<< orphan*/  ppnumber (char*) ; 
 scalar_t__ strtod (int,int /*<<< orphan*/ *) ; 
 int token ; 
 TYPE_9__ tval ; 
 int /*<<< orphan*/  warning (char*,int,char*) ; 

__attribute__((used)) static Symbol fcon(void) {
	if (*cp == '.')
		do
			cp++;
		while (map[*cp]&DIGIT);
	if (*cp == 'e' || *cp == 'E') {
		if (*++cp == '-' || *cp == '+')
			cp++;
		if (map[*cp]&DIGIT)
			do
				cp++;
			while (map[*cp]&DIGIT);
		else
			error("invalid floating constant `%S'\n", token,
				(char*)cp - token);
	}

	errno = 0;
	tval.u.c.v.d = strtod(token, NULL);
	if (errno == ERANGE)
		warning("overflow in floating constant `%S'\n", token,
			(char*)cp - token);
	if (*cp == 'f' || *cp == 'F') {
		++cp;
		if (tval.u.c.v.d > floattype->u.sym->u.limits.max.d)
			warning("overflow in floating constant `%S'\n", token,
				(char*)cp - token);
		tval.type = floattype;
	} else if (*cp == 'l' || *cp == 'L') {
		cp++;
		tval.type = longdouble;
	} else {
		if (tval.u.c.v.d > doubletype->u.sym->u.limits.max.d)
			warning("overflow in floating constant `%S'\n", token,
				(char*)cp - token);
		tval.type = doubletype;
	}
	ppnumber("floating");
	return &tval;
}