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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {scalar_t__ crc32; scalar_t__ pos; scalar_t__ count; int /*<<< orphan*/  memlimit; int /*<<< orphan*/  sequence; int /*<<< orphan*/ * index; int /*<<< orphan*/ ** index_ptr; } ;
typedef  TYPE_1__ lzma_index_coder ;
typedef  int /*<<< orphan*/  lzma_index ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  SEQ_INDICATOR ; 
 int /*<<< orphan*/ * lzma_index_init (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  my_max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
index_decoder_reset(lzma_index_coder *coder, const lzma_allocator *allocator,
		lzma_index **i, uint64_t memlimit)
{
	// Remember the pointer given by the application. We will set it
	// to point to the decoded Index only if decoding is successful.
	// Before that, keep it NULL so that applications can always safely
	// pass it to lzma_index_end() no matter did decoding succeed or not.
	coder->index_ptr = i;
	*i = NULL;

	// We always allocate a new lzma_index.
	coder->index = lzma_index_init(allocator);
	if (coder->index == NULL)
		return LZMA_MEM_ERROR;

	// Initialize the rest.
	coder->sequence = SEQ_INDICATOR;
	coder->memlimit = my_max(1, memlimit);
	coder->count = 0; // Needs to be initialized due to _memconfig().
	coder->pos = 0;
	coder->crc32 = 0;

	return LZMA_OK;
}