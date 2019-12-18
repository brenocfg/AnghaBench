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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct buf {int b_kvasize; scalar_t__ b_kvabase; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int /*<<< orphan*/  BUF_CHECK_UNMAPPED (struct buf*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  buffer_arena ; 
 int /*<<< orphan*/  buffreekvacnt ; 
 int /*<<< orphan*/  bufkvaspace ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unmapped_buf ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bufkva_free(struct buf *bp)
{

#ifdef INVARIANTS
	if (bp->b_kvasize == 0) {
		KASSERT(bp->b_kvabase == unmapped_buf &&
		    bp->b_data == unmapped_buf,
		    ("Leaked KVA space on %p", bp));
	} else if (buf_mapped(bp))
		BUF_CHECK_MAPPED(bp);
	else
		BUF_CHECK_UNMAPPED(bp);
#endif
	if (bp->b_kvasize == 0)
		return;

	vmem_free(buffer_arena, (vm_offset_t)bp->b_kvabase, bp->b_kvasize);
	counter_u64_add(bufkvaspace, -bp->b_kvasize);
	counter_u64_add(buffreekvacnt, 1);
	bp->b_data = bp->b_kvabase = unmapped_buf;
	bp->b_kvasize = 0;
}