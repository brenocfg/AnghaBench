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
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int FLAG_PA_CORE_IN_MM ; 
 unsigned int FLAG_PA_IS_EXEC ; 
 int /*<<< orphan*/  __flush_ptrace_access (struct page*,unsigned long,void*,unsigned long,unsigned int) ; 

void flush_uprobe_xol_access(struct page *page, unsigned long uaddr,
			     void *kaddr, unsigned long len)
{
	unsigned int flags = FLAG_PA_CORE_IN_MM|FLAG_PA_IS_EXEC;

	__flush_ptrace_access(page, uaddr, kaddr, len, flags);
}