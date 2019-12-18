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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ total_in; scalar_t__ total_out; } ;

/* Variables and functions */
 scalar_t__ MODE_COMPRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lzma_get_progress (TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ opt_mode ; 
 TYPE_1__* progress_strm ; 

__attribute__((used)) static void
progress_pos(uint64_t *in_pos,
		uint64_t *compressed_pos, uint64_t *uncompressed_pos)
{
	uint64_t out_pos;
	lzma_get_progress(progress_strm, in_pos, &out_pos);

	// It cannot have processed more input than it has been given.
	assert(*in_pos <= progress_strm->total_in);

	// It cannot have produced more output than it claims to have ready.
	assert(out_pos >= progress_strm->total_out);

	if (opt_mode == MODE_COMPRESS) {
		*compressed_pos = out_pos;
		*uncompressed_pos = *in_pos;
	} else {
		*compressed_pos = *in_pos;
		*uncompressed_pos = out_pos;
	}

	return;
}