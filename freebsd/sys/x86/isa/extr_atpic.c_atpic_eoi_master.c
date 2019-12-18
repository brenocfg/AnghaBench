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
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _atpic_eoi_master (struct intsrc*) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

__attribute__((used)) static void
atpic_eoi_master(struct intsrc *isrc)
{
#ifndef AUTO_EOI_1
	spinlock_enter();
	_atpic_eoi_master(isrc);
	spinlock_exit();
#endif
}