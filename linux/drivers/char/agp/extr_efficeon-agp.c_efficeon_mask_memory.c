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
 unsigned long page_to_phys (struct page*) ; 

__attribute__((used)) static inline unsigned long efficeon_mask_memory(struct page *page)
{
	unsigned long addr = page_to_phys(page);
	return addr | 0x00000001;
}