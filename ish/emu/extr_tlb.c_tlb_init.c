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
struct tlb {int /*<<< orphan*/  dirty_page; struct mem* mem; } ;
struct mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_PAGE_EMPTY ; 
 int /*<<< orphan*/  tlb_flush (struct tlb*) ; 

void tlb_init(struct tlb *tlb, struct mem *mem) {
    tlb->mem = mem;
    tlb->dirty_page = TLB_PAGE_EMPTY;
    tlb_flush(tlb);
}