#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* coder; int /*<<< orphan*/  (* end ) (TYPE_3__*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_7__ {TYPE_3__* buffer; TYPE_3__* hash; TYPE_3__* son; } ;
struct TYPE_8__ {TYPE_1__ lz; TYPE_2__ mf; int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_free (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_next_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
lz_encoder_end(void *coder_ptr, const lzma_allocator *allocator)
{
	lzma_coder *coder = coder_ptr;

	lzma_next_end(&coder->next, allocator);

	lzma_free(coder->mf.son, allocator);
	lzma_free(coder->mf.hash, allocator);
	lzma_free(coder->mf.buffer, allocator);

	if (coder->lz.end != NULL)
		coder->lz.end(coder->lz.coder, allocator);
	else
		lzma_free(coder->lz.coder, allocator);

	lzma_free(coder, allocator);
	return;
}