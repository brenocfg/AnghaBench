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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic64_add_return (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_timer_current ; 
 int /*<<< orphan*/  virt_timer_elapsed ; 
 int /*<<< orphan*/  virt_timer_list ; 

__attribute__((used)) static inline int virt_timer_forward(u64 elapsed)
{
	BUG_ON(!irqs_disabled());

	if (list_empty(&virt_timer_list))
		return 0;
	elapsed = atomic64_add_return(elapsed, &virt_timer_elapsed);
	return elapsed >= atomic64_read(&virt_timer_current);
}