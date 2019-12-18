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
 int /*<<< orphan*/  PAGE_KERNEL_NC ; 
 void* __kmap_pgprot (struct page*,unsigned long,int /*<<< orphan*/ ) ; 

void *kmap_noncoherent(struct page *page, unsigned long addr)
{
	return __kmap_pgprot(page, addr, PAGE_KERNEL_NC);
}