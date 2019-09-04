#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* stabtype ) (TYPE_1__*) ;int /*<<< orphan*/  (* stabsym ) (TYPE_1__*) ;} ;
struct TYPE_6__ {scalar_t__ sclass; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 scalar_t__ EXTERN ; 
 TYPE_5__* IR ; 
 scalar_t__ STATIC ; 
 scalar_t__ TYPEDEF ; 
 int /*<<< orphan*/  isfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

__attribute__((used)) static void typestab(Symbol p, void *cl) {
	if (!isfunc(p->type) && (p->sclass == EXTERN || p->sclass == STATIC) && IR->stabsym)
		(*IR->stabsym)(p);
	else if ((p->sclass == TYPEDEF || p->sclass == 0) && IR->stabtype)
		(*IR->stabtype)(p);
}