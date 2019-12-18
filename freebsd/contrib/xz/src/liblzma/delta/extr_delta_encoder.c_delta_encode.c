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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_5__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ next; } ;
typedef  TYPE_2__ lzma_delta_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  int /*<<< orphan*/  lzma_action ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_STREAM_END ; 
 int /*<<< orphan*/  copy_and_encode (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  encode_in_place (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 size_t my_min (size_t const,size_t const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
delta_encode(void *coder_ptr, const lzma_allocator *allocator,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size, lzma_action action)
{
	lzma_delta_coder *coder = coder_ptr;

	lzma_ret ret;

	if (coder->next.code == NULL) {
		const size_t in_avail = in_size - *in_pos;
		const size_t out_avail = out_size - *out_pos;
		const size_t size = my_min(in_avail, out_avail);

		copy_and_encode(coder, in + *in_pos, out + *out_pos, size);

		*in_pos += size;
		*out_pos += size;

		ret = action != LZMA_RUN && *in_pos == in_size
				? LZMA_STREAM_END : LZMA_OK;

	} else {
		const size_t out_start = *out_pos;

		ret = coder->next.code(coder->next.coder, allocator,
				in, in_pos, in_size, out, out_pos, out_size,
				action);

		encode_in_place(coder, out + out_start, *out_pos - out_start);
	}

	return ret;
}