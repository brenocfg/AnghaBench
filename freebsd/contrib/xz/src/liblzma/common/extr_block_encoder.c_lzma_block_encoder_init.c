#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_10__ {int /*<<< orphan*/ * update; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; TYPE_2__* coder; } ;
typedef  TYPE_1__ lzma_next_coder ;
struct TYPE_11__ {int /*<<< orphan*/  next; int /*<<< orphan*/  check; scalar_t__ pos; scalar_t__ uncompressed_size; scalar_t__ compressed_size; TYPE_3__* block; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_2__ lzma_block_coder ;
struct TYPE_12__ {int version; int /*<<< orphan*/  filters; scalar_t__ check; } ;
typedef  TYPE_3__ lzma_block ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 unsigned int LZMA_CHECK_ID_MAX ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  LZMA_UNSUPPORTED_CHECK ; 
 int /*<<< orphan*/  SEQ_CODE ; 
 int /*<<< orphan*/  block_encode ; 
 int /*<<< orphan*/  block_encoder_end ; 
 int /*<<< orphan*/  block_encoder_update ; 
 TYPE_2__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_check_init (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lzma_check_is_supported (scalar_t__) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/  const*,TYPE_3__*),TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_raw_encoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

extern lzma_ret
lzma_block_encoder_init(lzma_next_coder *next, const lzma_allocator *allocator,
		lzma_block *block)
{
	lzma_next_coder_init(&lzma_block_encoder_init, next, allocator);

	if (block == NULL)
		return LZMA_PROG_ERROR;

	// The contents of the structure may depend on the version so
	// check the version first.
	if (block->version > 1)
		return LZMA_OPTIONS_ERROR;

	// If the Check ID is not supported, we cannot calculate the check and
	// thus not create a proper Block.
	if ((unsigned int)(block->check) > LZMA_CHECK_ID_MAX)
		return LZMA_PROG_ERROR;

	if (!lzma_check_is_supported(block->check))
		return LZMA_UNSUPPORTED_CHECK;

	// Allocate and initialize *next->coder if needed.
	lzma_block_coder *coder = next->coder;
	if (coder == NULL) {
		coder = lzma_alloc(sizeof(lzma_block_coder), allocator);
		if (coder == NULL)
			return LZMA_MEM_ERROR;

		next->coder = coder;
		next->code = &block_encode;
		next->end = &block_encoder_end;
		next->update = &block_encoder_update;
		coder->next = LZMA_NEXT_CODER_INIT;
	}

	// Basic initializations
	coder->sequence = SEQ_CODE;
	coder->block = block;
	coder->compressed_size = 0;
	coder->uncompressed_size = 0;
	coder->pos = 0;

	// Initialize the check
	lzma_check_init(&coder->check, block->check);

	// Initialize the requested filters.
	return lzma_raw_encoder_init(&coder->next, allocator, block->filters);
}