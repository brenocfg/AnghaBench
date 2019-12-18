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
struct TYPE_2__ {int /*<<< orphan*/  copros; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mm_needs_flush_escalation(struct mm_struct *mm)
{
	/*
	 * P9 nest MMU has issues with the page walk cache
	 * caching PTEs and not flushing them properly when
	 * RIC = 0 for a PID/LPID invalidate
	 */
	if (atomic_read(&mm->context.copros) > 0)
		return true;
	return false;
}