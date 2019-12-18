#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* coder; int /*<<< orphan*/ * end; } ;
struct TYPE_5__ {TYPE_1__ lzma; } ;
typedef  TYPE_2__ lzma_lzma2_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_free (TYPE_2__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
lzma2_decoder_end(void *coder_ptr, const lzma_allocator *allocator)
{
	lzma_lzma2_coder *coder = coder_ptr;

	assert(coder->lzma.end == NULL);
	lzma_free(coder->lzma.coder, allocator);

	lzma_free(coder, allocator);

	return;
}