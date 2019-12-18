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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crng_ready () ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  destroy_timer_on_stack (struct timer_list*) ; 
 int /*<<< orphan*/  entropy_timer ; 
 int /*<<< orphan*/  input_pool ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mix_pool_bytes (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 void* random_get_entropy () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  timer_pending (struct timer_list*) ; 
 int /*<<< orphan*/  timer_setup_on_stack (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void try_to_generate_entropy(void)
{
	struct {
		unsigned long now;
		struct timer_list timer;
	} stack;

	stack.now = random_get_entropy();

	/* Slow counter - or none. Don't even bother */
	if (stack.now == random_get_entropy())
		return;

	timer_setup_on_stack(&stack.timer, entropy_timer, 0);
	while (!crng_ready()) {
		if (!timer_pending(&stack.timer))
			mod_timer(&stack.timer, jiffies+1);
		mix_pool_bytes(&input_pool, &stack.now, sizeof(stack.now));
		schedule();
		stack.now = random_get_entropy();
	}

	del_timer_sync(&stack.timer);
	destroy_timer_on_stack(&stack.timer);
	mix_pool_bytes(&input_pool, &stack.now, sizeof(stack.now));
}