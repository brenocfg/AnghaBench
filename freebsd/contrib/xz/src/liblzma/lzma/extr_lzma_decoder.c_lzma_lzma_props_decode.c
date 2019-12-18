#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_5__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 TYPE_1__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ lzma_lzma_lclppb_decode (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  unaligned_read32le (int /*<<< orphan*/  const*) ; 

extern lzma_ret
lzma_lzma_props_decode(void **options, const lzma_allocator *allocator,
		const uint8_t *props, size_t props_size)
{
	if (props_size != 5)
		return LZMA_OPTIONS_ERROR;

	lzma_options_lzma *opt
			= lzma_alloc(sizeof(lzma_options_lzma), allocator);
	if (opt == NULL)
		return LZMA_MEM_ERROR;

	if (lzma_lzma_lclppb_decode(opt, props[0]))
		goto error;

	// All dictionary sizes are accepted, including zero. LZ decoder
	// will automatically use a dictionary at least a few KiB even if
	// a smaller dictionary is requested.
	opt->dict_size = unaligned_read32le(props + 1);

	opt->preset_dict = NULL;
	opt->preset_dict_size = 0;

	*options = opt;

	return LZMA_OK;

error:
	lzma_free(opt, allocator);
	return LZMA_OPTIONS_ERROR;
}