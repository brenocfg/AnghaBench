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
struct TYPE_3__ {struct TYPE_3__* lzma; } ;
typedef  TYPE_1__ lzma_lzma2_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
lzma2_encoder_end(void *coder_ptr, const lzma_allocator *allocator)
{
	lzma_lzma2_coder *coder = coder_ptr;
	lzma_free(coder->lzma, allocator);
	lzma_free(coder, allocator);
	return;
}