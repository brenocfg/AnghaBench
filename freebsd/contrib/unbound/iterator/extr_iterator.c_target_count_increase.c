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
struct iter_qstate {int* target_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  target_count_create (struct iter_qstate*) ; 

__attribute__((used)) static void
target_count_increase(struct iter_qstate* iq, int num)
{
	target_count_create(iq);
	if(iq->target_count)
		iq->target_count[1] += num;
}