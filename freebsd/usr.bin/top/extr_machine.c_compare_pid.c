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
struct kinfo_proc {scalar_t__ ki_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
compare_pid(const void *p1, const void *p2)
{
	const struct kinfo_proc * const *pp1 = p1;
	const struct kinfo_proc * const *pp2 = p2;

	assert((*pp2)->ki_pid >= 0 && (*pp1)->ki_pid >= 0);

	return ((*pp1)->ki_pid - (*pp2)->ki_pid);
}