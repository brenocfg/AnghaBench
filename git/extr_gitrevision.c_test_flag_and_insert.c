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
struct prio_queue {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  prio_queue_put (struct prio_queue*,struct commit*) ; 

__attribute__((used)) static inline void test_flag_and_insert(struct prio_queue *q, struct commit *c, int flag)
{
	if (c->object.flags & flag)
		return;

	c->object.flags |= flag;
	prio_queue_put(q, c);
}