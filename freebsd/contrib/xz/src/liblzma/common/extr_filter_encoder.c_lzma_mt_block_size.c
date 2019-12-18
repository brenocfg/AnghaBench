#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ (* block_size ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ lzma_filter_encoder ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ lzma_filter ;

/* Variables and functions */
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 TYPE_1__* encoder_find (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

extern uint64_t
lzma_mt_block_size(const lzma_filter *filters)
{
	uint64_t max = 0;

	for (size_t i = 0; filters[i].id != LZMA_VLI_UNKNOWN; ++i) {
		const lzma_filter_encoder *const fe
				= encoder_find(filters[i].id);
		if (fe->block_size != NULL) {
			const uint64_t size
					= fe->block_size(filters[i].options);
			if (size == 0)
				return 0;

			if (size > max)
				max = size;
		}
	}

	return max;
}