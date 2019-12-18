#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * bufs_mem; int /*<<< orphan*/ * bufs; } ;
typedef  TYPE_1__ lzma_outq ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_free (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

extern void
lzma_outq_end(lzma_outq *outq, const lzma_allocator *allocator)
{
	lzma_free(outq->bufs, allocator);
	outq->bufs = NULL;

	lzma_free(outq->bufs_mem, allocator);
	outq->bufs_mem = NULL;

	return;
}