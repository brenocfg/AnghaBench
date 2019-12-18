#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {scalar_t__ start_offset; } ;
typedef  TYPE_1__ lzma_options_bcj ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 TYPE_1__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unaligned_read32le (int /*<<< orphan*/  const*) ; 

extern lzma_ret
lzma_simple_props_decode(void **options, const lzma_allocator *allocator,
		const uint8_t *props, size_t props_size)
{
	if (props_size == 0)
		return LZMA_OK;

	if (props_size != 4)
		return LZMA_OPTIONS_ERROR;

	lzma_options_bcj *opt = lzma_alloc(
			sizeof(lzma_options_bcj), allocator);
	if (opt == NULL)
		return LZMA_MEM_ERROR;

	opt->start_offset = unaligned_read32le(props);

	// Don't leave an options structure allocated if start_offset is zero.
	if (opt->start_offset == 0)
		lzma_free(opt, allocator);
	else
		*options = opt;

	return LZMA_OK;
}