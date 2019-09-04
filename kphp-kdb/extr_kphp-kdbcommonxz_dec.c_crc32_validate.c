#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xz_dec {int pos; int crc32; } ;
struct xz_buf {scalar_t__ in_pos; scalar_t__ in_size; int* in; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 int XZ_DATA_ERROR ; 
 int XZ_OK ; 
 int XZ_STREAM_END ; 

__attribute__((used)) static enum xz_ret crc32_validate(struct xz_dec *s, struct xz_buf *b)
{
	do {
		if (b->in_pos == b->in_size)
			return XZ_OK;

		if (((s->crc32 >> s->pos) & 0xFF) != b->in[b->in_pos++])
			return XZ_DATA_ERROR;

		s->pos += 8;

	} while (s->pos < 32);

	s->crc32 = 0;
	s->pos = 0;

	return XZ_STREAM_END;
}