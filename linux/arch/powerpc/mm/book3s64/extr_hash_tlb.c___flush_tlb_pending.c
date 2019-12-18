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
struct ppc64_tlb_batch {int index; int /*<<< orphan*/  ssize; int /*<<< orphan*/  psize; int /*<<< orphan*/ * pte; int /*<<< orphan*/ * vpn; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_hash_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_hash_range (int,int) ; 
 int mm_is_thread_local (int /*<<< orphan*/ ) ; 

void __flush_tlb_pending(struct ppc64_tlb_batch *batch)
{
	int i, local;

	i = batch->index;
	local = mm_is_thread_local(batch->mm);
	if (i == 1)
		flush_hash_page(batch->vpn[0], batch->pte[0],
				batch->psize, batch->ssize, local);
	else
		flush_hash_range(i, local);
	batch->index = 0;
}