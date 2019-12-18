#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
typedef  TYPE_1__* Tree ;
struct TYPE_6__ {int op; struct TYPE_6__** kids; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  where ; 

Tree tree(int op, Type type, Tree left, Tree right) {
	Tree p;

	NEW0(p, where);
	p->op = op;
	p->type = type;
	p->kids[0] = left;
	p->kids[1] = right;
	return p;
}