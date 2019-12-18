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

/* Variables and functions */
 int /*<<< orphan*/  insn_page_in_use ; 
 int /*<<< orphan*/  set_memory_nx (unsigned long,int) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_s390_insn_page(void *page)
{
	set_memory_nx((unsigned long) page, 1);
	xchg(&insn_page_in_use, 0);
}