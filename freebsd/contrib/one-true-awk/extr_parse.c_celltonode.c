#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int csub; int /*<<< orphan*/  ctype; } ;
struct TYPE_7__ {int /*<<< orphan*/  ntype; } ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  NVALUE ; 
 int /*<<< orphan*/  OCELL ; 
 TYPE_1__* node1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

Node *celltonode(Cell *a, int b)
{
	Node *x;

	a->ctype = OCELL;
	a->csub = b;
	x = node1(0, (Node *) a);
	x->ntype = NVALUE;
	return(x);
}