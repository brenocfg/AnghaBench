#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ op; int /*<<< orphan*/ * syms; } ;

/* Variables and functions */
 scalar_t__ LABEL ; 
 scalar_t__ V ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  equatelab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findlabel (int) ; 
 TYPE_1__* forest ; 
 int /*<<< orphan*/  list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnode (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset () ; 

__attribute__((used)) static void labelnode(int lab) {
	assert(lab);
	if (forest && forest->op == LABEL+V)
		equatelab(findlabel(lab), forest->syms[0]);
	else
		list(newnode(LABEL+V, NULL, NULL, findlabel(lab)));
	reset();
}