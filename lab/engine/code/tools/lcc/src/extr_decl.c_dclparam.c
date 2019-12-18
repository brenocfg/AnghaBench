#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char* Type ;
struct TYPE_5__ {scalar_t__ scope; char src; int sclass; char* type; int defined; } ;
typedef  TYPE_1__* Symbol ;
typedef  char Coordinate ;

/* Variables and functions */
 int AUTO ; 
 int /*<<< orphan*/  FUNC ; 
 int REGISTER ; 
 char* atop (char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  expr1 (int /*<<< orphan*/ ) ; 
 char gettok () ; 
 int /*<<< orphan*/  identifiers ; 
 TYPE_1__* install (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ isarray (char*) ; 
 scalar_t__ isfunc (char*) ; 
 scalar_t__ isstruct (char*) ; 
 scalar_t__ isvolatile (char*) ; 
 scalar_t__ level ; 
 TYPE_1__* lookup (char*,int /*<<< orphan*/ ) ; 
 char* ptr (char*) ; 
 int /*<<< orphan*/  stringf (char*,char*) ; 
 char t ; 
 int /*<<< orphan*/  warning (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Symbol dclparam(int sclass, char *id, Type ty, Coordinate *pos) {
	Symbol p;

	if (isfunc(ty))
		ty = ptr(ty);
	else if (isarray(ty))
		ty = atop(ty);
	if (sclass == 0)
		sclass = AUTO;
	else if (sclass != REGISTER) {
		error("invalid storage class `%k' for `%t%s\n",
			sclass, ty, stringf(id ? " %s'" : "' parameter", id));
		sclass = AUTO;
	} else if (isvolatile(ty) || isstruct(ty)) {
		warning("register declaration ignored for `%t%s\n",
			ty, stringf(id ? " %s'" : "' parameter", id));
		sclass = AUTO;
	}

	p = lookup(id, identifiers);
	if (p && p->scope == level)
		error("duplicate declaration for `%s' previously declared at %w\n", id, &p->src);

	else
		p = install(id, &identifiers, level, FUNC);
	p->sclass = sclass;
	p->src = *pos;
	p->type = ty;
	p->defined = 1;
	if (t == '=') {
		error("illegal initialization for parameter `%s'\n", id);
		t = gettok();
		(void)expr1(0);
	}
	return p;
}