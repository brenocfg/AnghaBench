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
 int /*<<< orphan*/  __dma_flush_area (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

void arch_dma_prep_coherent(struct page *page, size_t size)
{
	__dma_flush_area(page_address(page), size);
}