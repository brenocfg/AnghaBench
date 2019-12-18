#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_2__ {scalar_t__ start_offset; } ;
typedef  TYPE_1__ lzma_options_bcj ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  unaligned_write32le (int /*<<< orphan*/ *,scalar_t__) ; 

extern lzma_ret
lzma_simple_props_encode(const void *options, uint8_t *out)
{
	const lzma_options_bcj *const opt = options;

	// The default start offset is zero, so we don't need to store any
	// options unless the start offset is non-zero.
	if (opt == NULL || opt->start_offset == 0)
		return LZMA_OK;

	unaligned_write32le(out, opt->start_offset);

	return LZMA_OK;
}