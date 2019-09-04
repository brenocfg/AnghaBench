#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ proto; } ;
struct TYPE_13__ {TYPE_1__ f; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
struct TYPE_14__ {TYPE_4__* type; } ;
typedef  TYPE_3__* Symbol ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  append (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freturn (TYPE_4__*) ; 
 TYPE_4__* func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltov (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printdecl (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* voidtype ; 

void printproto(Symbol p, Symbol callee[]) {
	if (p->type->u.f.proto)
		printdecl(p, p->type);
	else {
		int i;
		List list = 0;
		if (callee[0] == 0)
			list = append(voidtype, list);
		else
			for (i = 0; callee[i]; i++)
				list = append(callee[i]->type, list);
		printdecl(p, func(freturn(p->type), ltov(&list, PERM), 0));
	}
}