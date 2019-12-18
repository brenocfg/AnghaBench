#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr; TYPE_1__** checks; } ;
struct TYPE_3__ {int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 TYPE_2__ check_vector ; 
 int /*<<< orphan*/  drop_attr_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_lock () ; 
 int /*<<< orphan*/  vector_unlock () ; 

__attribute__((used)) static void drop_all_attr_stacks(void)
{
	int i;

	vector_lock();

	for (i = 0; i < check_vector.nr; i++) {
		drop_attr_stack(&check_vector.checks[i]->stack);
	}

	vector_unlock();
}