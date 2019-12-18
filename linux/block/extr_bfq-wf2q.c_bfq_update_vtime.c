#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct bfq_service_tree {scalar_t__ vtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_forget_idle (struct bfq_service_tree*) ; 

__attribute__((used)) static void bfq_update_vtime(struct bfq_service_tree *st, u64 new_value)
{
	if (new_value > st->vtime) {
		st->vtime = new_value;
		bfq_forget_idle(st);
	}
}