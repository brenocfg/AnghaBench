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
struct mm_struct {int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_range_common (struct mm_struct*,unsigned long,unsigned long,int) ; 

__attribute__((used)) static void fix_range(struct mm_struct *mm, unsigned long start_addr,
		      unsigned long end_addr, int force)
{
	/*
	 * Don't bother flushing if this address space is about to be
	 * destroyed.
	 */
	if (atomic_read(&mm->mm_users) == 0)
		return;

	fix_range_common(mm, start_addr, end_addr, force);
}