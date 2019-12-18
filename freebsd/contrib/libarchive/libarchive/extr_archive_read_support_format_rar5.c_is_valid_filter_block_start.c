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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ write_ptr; scalar_t__ last_block_start; scalar_t__ last_block_length; } ;
struct rar5 {TYPE_1__ cstate; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int is_valid_filter_block_start(struct rar5* rar,
    uint32_t start)
{
	const int64_t block_start = (ssize_t) start + rar->cstate.write_ptr;
	const int64_t last_bs = rar->cstate.last_block_start;
	const ssize_t last_bl = rar->cstate.last_block_length;

	if(last_bs == 0 || last_bl == 0) {
		/* We didn't have any filters yet, so accept this offset. */
		return 1;
	}

	if(block_start >= last_bs + last_bl) {
		/* Current offset is bigger than last block's end offset, so
		 * accept current offset. */
		return 1;
	}

	/* Any other case is not a normal situation and we should fail. */
	return 0;
}