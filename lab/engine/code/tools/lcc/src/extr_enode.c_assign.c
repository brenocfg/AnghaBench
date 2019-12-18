#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
typedef  TYPE_2__* Tree ;
struct TYPE_22__ {TYPE_1__* type; } ;
struct TYPE_21__ {scalar_t__ size; struct TYPE_21__* type; } ;

/* Variables and functions */
 int Aflag ; 
 scalar_t__ eqtype (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* inttype ; 
 scalar_t__ isarith (TYPE_1__*) ; 
 scalar_t__ isconst (TYPE_1__*) ; 
 scalar_t__ isenum (TYPE_1__*) ; 
 scalar_t__ isnullptr (TYPE_2__*) ; 
 scalar_t__ isptr (TYPE_1__*) ; 
 scalar_t__ isstruct (TYPE_1__*) ; 
 scalar_t__ isvoidptr (TYPE_1__*) ; 
 scalar_t__ isvolatile (TYPE_1__*) ; 
 TYPE_1__* unqual (TYPE_1__*) ; 
 int /*<<< orphan*/  warning (char*,TYPE_1__*,TYPE_1__*) ; 

Type assign(Type xty, Tree e) {
	Type yty = unqual(e->type);

	xty = unqual(xty);
	if (isenum(xty))
		xty = xty->type;
	if (xty->size == 0 || yty->size == 0)
		return NULL;
	if ( (isarith(xty) && isarith(yty))
	||  (isstruct(xty) && xty == yty))
		return xty;
	if (isptr(xty) && isnullptr(e))
		return xty;
	if (((isvoidptr(xty) && isptr(yty))
	  || (isptr(xty)     && isvoidptr(yty)))
	&& (  (isconst(xty->type)    || !isconst(yty->type))
	   && (isvolatile(xty->type) || !isvolatile(yty->type))))
		return xty;

	if ((isptr(xty) && isptr(yty)
	    && eqtype(unqual(xty->type), unqual(yty->type), 1))
	&&  (  (isconst(xty->type)    || !isconst(yty->type))
	    && (isvolatile(xty->type) || !isvolatile(yty->type))))
		return xty;
	if (isptr(xty) && isptr(yty)
	&& (  (isconst(xty->type)    || !isconst(yty->type))
	   && (isvolatile(xty->type) || !isvolatile(yty->type)))) {
		Type lty = unqual(xty->type), rty = unqual(yty->type);
		if ((isenum(lty) && rty == inttype)
		||  (isenum(rty) && lty == inttype)) {
			if (Aflag >= 1)
				warning("assignment between `%t' and `%t' is compiler-dependent\n",
					xty, yty);
			return xty;
		}
	}
	return NULL;
}