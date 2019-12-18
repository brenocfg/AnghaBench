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
struct async_submit_ctl {void** scribble; int flags; } ;

/* Variables and functions */
 int ASYNC_TX_XOR_ZERO_DST ; 
 int /*<<< orphan*/  MAX_XOR_BLOCKS ; 
 int /*<<< orphan*/  async_tx_sync_epilog (struct async_submit_ctl*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  xor_blocks (int,size_t,void*,void**) ; 

__attribute__((used)) static void
do_sync_xor(struct page *dest, struct page **src_list, unsigned int offset,
	    int src_cnt, size_t len, struct async_submit_ctl *submit)
{
	int i;
	int xor_src_cnt = 0;
	int src_off = 0;
	void *dest_buf;
	void **srcs;

	if (submit->scribble)
		srcs = submit->scribble;
	else
		srcs = (void **) src_list;

	/* convert to buffer pointers */
	for (i = 0; i < src_cnt; i++)
		if (src_list[i])
			srcs[xor_src_cnt++] = page_address(src_list[i]) + offset;
	src_cnt = xor_src_cnt;
	/* set destination address */
	dest_buf = page_address(dest) + offset;

	if (submit->flags & ASYNC_TX_XOR_ZERO_DST)
		memset(dest_buf, 0, len);

	while (src_cnt > 0) {
		/* process up to 'MAX_XOR_BLOCKS' sources */
		xor_src_cnt = min(src_cnt, MAX_XOR_BLOCKS);
		xor_blocks(xor_src_cnt, len, dest_buf, &srcs[src_off]);

		/* drop completed sources */
		src_cnt -= xor_src_cnt;
		src_off += xor_src_cnt;
	}

	async_tx_sync_epilog(submit);
}