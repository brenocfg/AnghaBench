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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __radix__flush_tlb_range_psize (struct mm_struct*,unsigned long,unsigned long,int,int) ; 

__attribute__((used)) static void radix__flush_tlb_pwc_range_psize(struct mm_struct *mm, unsigned long start,
				  unsigned long end, int psize)
{
	__radix__flush_tlb_range_psize(mm, start, end, psize, true);
}