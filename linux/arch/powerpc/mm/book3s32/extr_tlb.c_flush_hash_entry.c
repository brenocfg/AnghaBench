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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ Hash ; 
 unsigned long PAGE_MASK ; 
 unsigned long __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_hash_pages (int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 

void flush_hash_entry(struct mm_struct *mm, pte_t *ptep, unsigned long addr)
{
	unsigned long ptephys;

	if (Hash) {
		ptephys = __pa(ptep) & PAGE_MASK;
		flush_hash_pages(mm->context.id, addr, ptephys, 1);
	}
}