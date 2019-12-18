#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_9__ {int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; TYPE_3__* coder; } ;
typedef  TYPE_2__ lzma_next_coder ;
struct TYPE_8__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; scalar_t__ dict_size; } ;
struct TYPE_10__ {int picky; int /*<<< orphan*/  memusage; int /*<<< orphan*/  memlimit; scalar_t__ uncompressed_size; TYPE_1__ options; scalar_t__ pos; int /*<<< orphan*/  sequence; int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ lzma_alone_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEMUSAGE_BASE ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  SEQ_PROPERTIES ; 
 int /*<<< orphan*/  alone_decode ; 
 int /*<<< orphan*/  alone_decoder_end ; 
 int /*<<< orphan*/  alone_decoder_memconfig ; 
 TYPE_3__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int),TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  my_max (int,int /*<<< orphan*/ ) ; 

extern lzma_ret
lzma_alone_decoder_init(lzma_next_coder *next, const lzma_allocator *allocator,
		uint64_t memlimit, bool picky)
{
	lzma_next_coder_init(&lzma_alone_decoder_init, next, allocator);

	lzma_alone_coder *coder = next->coder;

	if (coder == NULL) {
		coder = lzma_alloc(sizeof(lzma_alone_coder), allocator);
		if (coder == NULL)
			return LZMA_MEM_ERROR;

		next->coder = coder;
		next->code = &alone_decode;
		next->end = &alone_decoder_end;
		next->memconfig = &alone_decoder_memconfig;
		coder->next = LZMA_NEXT_CODER_INIT;
	}

	coder->sequence = SEQ_PROPERTIES;
	coder->picky = picky;
	coder->pos = 0;
	coder->options.dict_size = 0;
	coder->options.preset_dict = NULL;
	coder->options.preset_dict_size = 0;
	coder->uncompressed_size = 0;
	coder->memlimit = my_max(1, memlimit);
	coder->memusage = LZMA_MEMUSAGE_BASE;

	return LZMA_OK;
}