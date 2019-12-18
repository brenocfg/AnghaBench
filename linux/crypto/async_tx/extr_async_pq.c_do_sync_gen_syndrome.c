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
struct page {int dummy; } ;
struct async_submit_ctl {void** scribble; int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gen_syndrome ) (int,size_t,void**) ;int /*<<< orphan*/  (* xor_syndrome ) (int,int,int,size_t,void**) ;} ;

/* Variables and functions */
 int ASYNC_TX_PQ_XOR_DST ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  async_tx_sync_epilog (struct async_submit_ctl*) ; 
 void* page_address (struct page*) ; 
 TYPE_1__ raid6_call ; 
 scalar_t__ raid6_empty_zero_page ; 
 int /*<<< orphan*/  stub1 (int,int,int,size_t,void**) ; 
 int /*<<< orphan*/  stub2 (int,size_t,void**) ; 

__attribute__((used)) static void
do_sync_gen_syndrome(struct page **blocks, unsigned int offset, int disks,
		     size_t len, struct async_submit_ctl *submit)
{
	void **srcs;
	int i;
	int start = -1, stop = disks - 3;

	if (submit->scribble)
		srcs = submit->scribble;
	else
		srcs = (void **) blocks;

	for (i = 0; i < disks; i++) {
		if (blocks[i] == NULL) {
			BUG_ON(i > disks - 3); /* P or Q can't be zero */
			srcs[i] = (void*)raid6_empty_zero_page;
		} else {
			srcs[i] = page_address(blocks[i]) + offset;
			if (i < disks - 2) {
				stop = i;
				if (start == -1)
					start = i;
			}
		}
	}
	if (submit->flags & ASYNC_TX_PQ_XOR_DST) {
		BUG_ON(!raid6_call.xor_syndrome);
		if (start >= 0)
			raid6_call.xor_syndrome(disks, start, stop, len, srcs);
	} else
		raid6_call.gen_syndrome(disks, len, srcs);
	async_tx_sync_epilog(submit);
}