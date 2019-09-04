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
struct xz_dec {int allow_buf_error; int /*<<< orphan*/  mode; } ;
struct xz_buf {size_t in_pos; size_t out_pos; size_t in_size; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 scalar_t__ DEC_IS_SINGLE (int /*<<< orphan*/ ) ; 
 int XZ_BUF_ERROR ; 
 int XZ_DATA_ERROR ; 
 int XZ_OK ; 
 int XZ_STREAM_END ; 
 int dec_main (struct xz_dec*,struct xz_buf*) ; 
 int /*<<< orphan*/  xz_dec_reset (struct xz_dec*) ; 

enum xz_ret xz_dec_run(struct xz_dec *s, struct xz_buf *b)
{
	size_t in_start;
	size_t out_start;
	enum xz_ret ret;

	if (DEC_IS_SINGLE(s->mode))
		xz_dec_reset(s);

	in_start = b->in_pos;
	out_start = b->out_pos;
	ret = dec_main(s, b);

	if (DEC_IS_SINGLE(s->mode)) {
		if (ret == XZ_OK)
			ret = b->in_pos == b->in_size
					? XZ_DATA_ERROR : XZ_BUF_ERROR;

		if (ret != XZ_STREAM_END) {
			b->in_pos = in_start;
			b->out_pos = out_start;
		}

	} else if (ret == XZ_OK && in_start == b->in_pos
			&& out_start == b->out_pos) {
		if (s->allow_buf_error)
			ret = XZ_BUF_ERROR;

		s->allow_buf_error = 1;
	} else {
		s->allow_buf_error = 0;
	}

	return ret;
}