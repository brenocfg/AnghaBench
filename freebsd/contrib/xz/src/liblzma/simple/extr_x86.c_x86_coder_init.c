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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ prev_pos; scalar_t__ prev_mask; } ;
typedef  TYPE_1__ lzma_simple_x86 ;
struct TYPE_7__ {TYPE_1__* simple; } ;
typedef  TYPE_2__ lzma_simple_coder ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_8__ {TYPE_2__* coder; } ;
typedef  TYPE_3__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_filter_info ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 scalar_t__ const LZMA_OK ; 
 scalar_t__ lzma_simple_coder_init (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  x86_code ; 

__attribute__((used)) static lzma_ret
x86_coder_init(lzma_next_coder *next, const lzma_allocator *allocator,
		const lzma_filter_info *filters, bool is_encoder)
{
	const lzma_ret ret = lzma_simple_coder_init(next, allocator, filters,
			&x86_code, sizeof(lzma_simple_x86), 5, 1, is_encoder);

	if (ret == LZMA_OK) {
		lzma_simple_coder *coder = next->coder;
		lzma_simple_x86 *simple = coder->simple;
		simple->prev_mask = 0;
		simple->prev_pos = (uint32_t)(-5);
	}

	return ret;
}