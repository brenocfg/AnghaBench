#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_8__ {int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; TYPE_2__* coder; } ;
typedef  TYPE_1__ lzma_next_coder ;
struct TYPE_9__ {int /*<<< orphan*/ * index; } ;
typedef  TYPE_2__ lzma_index_coder ;
typedef  int /*<<< orphan*/  lzma_index ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  index_decode ; 
 int /*<<< orphan*/  index_decoder_end ; 
 int /*<<< orphan*/  index_decoder_memconfig ; 
 int /*<<< orphan*/  index_decoder_reset (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_2__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ),TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static lzma_ret
index_decoder_init(lzma_next_coder *next, const lzma_allocator *allocator,
		lzma_index **i, uint64_t memlimit)
{
	lzma_next_coder_init(&index_decoder_init, next, allocator);

	if (i == NULL)
		return LZMA_PROG_ERROR;

	lzma_index_coder *coder = next->coder;
	if (coder == NULL) {
		coder = lzma_alloc(sizeof(lzma_index_coder), allocator);
		if (coder == NULL)
			return LZMA_MEM_ERROR;

		next->coder = coder;
		next->code = &index_decode;
		next->end = &index_decoder_end;
		next->memconfig = &index_decoder_memconfig;
		coder->index = NULL;
	} else {
		lzma_index_end(coder->index, allocator);
	}

	return index_decoder_reset(coder, allocator, i, memlimit);
}