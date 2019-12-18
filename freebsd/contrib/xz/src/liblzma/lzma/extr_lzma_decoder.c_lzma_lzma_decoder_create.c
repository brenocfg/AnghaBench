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
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {int /*<<< orphan*/  preset_dict_size; int /*<<< orphan*/  preset_dict; int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;
typedef  int /*<<< orphan*/  lzma_lzma1_decoder ;
struct TYPE_7__ {int /*<<< orphan*/  preset_dict_size; int /*<<< orphan*/  preset_dict; int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_2__ lzma_lz_options ;
struct TYPE_8__ {int /*<<< orphan*/ * set_uncompressed; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * code; int /*<<< orphan*/ * coder; } ;
typedef  TYPE_3__ lzma_lz_decoder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/ * lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_decode ; 
 int /*<<< orphan*/  lzma_decoder_reset ; 
 int /*<<< orphan*/  lzma_decoder_uncompressed ; 

extern lzma_ret
lzma_lzma_decoder_create(lzma_lz_decoder *lz, const lzma_allocator *allocator,
		const void *opt, lzma_lz_options *lz_options)
{
	if (lz->coder == NULL) {
		lz->coder = lzma_alloc(sizeof(lzma_lzma1_decoder), allocator);
		if (lz->coder == NULL)
			return LZMA_MEM_ERROR;

		lz->code = &lzma_decode;
		lz->reset = &lzma_decoder_reset;
		lz->set_uncompressed = &lzma_decoder_uncompressed;
	}

	// All dictionary sizes are OK here. LZ decoder will take care of
	// the special cases.
	const lzma_options_lzma *options = opt;
	lz_options->dict_size = options->dict_size;
	lz_options->preset_dict = options->preset_dict;
	lz_options->preset_dict_size = options->preset_dict_size;

	return LZMA_OK;
}