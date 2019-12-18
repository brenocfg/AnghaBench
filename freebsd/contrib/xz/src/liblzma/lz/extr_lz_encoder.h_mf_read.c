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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ read_ahead; size_t read_pos; scalar_t__ buffer; } ;
typedef  TYPE_1__ lzma_mf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t const) ; 
 size_t my_min (size_t const,size_t) ; 

__attribute__((used)) static inline void
mf_read(lzma_mf *mf, uint8_t *out, size_t *out_pos, size_t out_size,
		size_t *left)
{
	const size_t out_avail = out_size - *out_pos;
	const size_t copy_size = my_min(out_avail, *left);

	assert(mf->read_ahead == 0);
	assert(mf->read_pos >= *left);

	memcpy(out + *out_pos, mf->buffer + mf->read_pos - *left,
			copy_size);

	*out_pos += copy_size;
	*left -= copy_size;
	return;
}