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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 int FOLL_GET ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PUD_MASK ; 
 struct page* pud_page (int /*<<< orphan*/ ) ; 

struct page *
follow_huge_pud(struct mm_struct *mm, unsigned long address,
		pud_t *pud, int flags)
{
	if (flags & FOLL_GET)
		return NULL;

	return pud_page(*pud) + ((address & ~PUD_MASK) >> PAGE_SHIFT);
}