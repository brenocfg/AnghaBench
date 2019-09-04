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
typedef  TYPE_1__* Tree ;
struct TYPE_5__ {scalar_t__ op; struct TYPE_5__** kids; } ;

/* Variables and functions */
 scalar_t__ RIGHT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

Tree rightkid(Tree p) {
	while (p && p->op == RIGHT)
		if (p->kids[1])
			p = p->kids[1];
		else if (p->kids[0])
			p = p->kids[0];
		else
			assert(0);
	assert(p);
	return p;
}