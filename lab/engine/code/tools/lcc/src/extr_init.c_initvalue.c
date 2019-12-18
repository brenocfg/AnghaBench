#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char* Type ;
typedef  TYPE_1__* Tree ;
struct TYPE_8__ {int /*<<< orphan*/  op; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ CNST ; 
 char* assign (char*,TYPE_1__*) ; 
 TYPE_1__* cast (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  consttree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 TYPE_1__* expr1 (int /*<<< orphan*/ ) ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 int /*<<< orphan*/  needconst ; 
 TYPE_1__* retype (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Tree initvalue(Type ty) {
	Type aty;
	Tree e;

	needconst++;
	e = expr1(0);
	if ((aty = assign(ty, e)) != NULL)
		e = cast(e, aty);
	else {
		error("invalid initialization type; found `%t' expected `%t'\n",
			e->type,  ty);
		e = retype(consttree(0, inttype), ty);
	}
	needconst--;
	if (generic(e->op) != CNST) {
		error("initializer must be constant\n");
		e = retype(consttree(0, inttype), ty);
	}
	return e;
}