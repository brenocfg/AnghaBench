#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* Tree ;
struct TYPE_11__ {int /*<<< orphan*/ * loc; } ;
struct TYPE_12__ {TYPE_1__ c; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/ * sym; int /*<<< orphan*/  v; } ;
struct TYPE_14__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRG ; 
 int /*<<< orphan*/  GLOBAL ; 
 int /*<<< orphan*/  STATIC ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 TYPE_5__* constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * genident (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* idtree (int /*<<< orphan*/ *) ; 
 scalar_t__ isarray (int /*<<< orphan*/ ) ; 
 TYPE_4__* simplify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Tree cvtconst(Tree p) {
	Symbol q = constant(p->type, p->u.v);
	Tree e;

	if (q->u.c.loc == NULL)
		q->u.c.loc = genident(STATIC, p->type, GLOBAL);
	if (isarray(p->type)) {
		e = simplify(ADDRG, atop(p->type), NULL, NULL);
		e->u.sym = q->u.c.loc;
	} else
		e = idtree(q->u.c.loc);
	return e;
}