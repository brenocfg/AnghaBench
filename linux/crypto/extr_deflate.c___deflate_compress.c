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
typedef  int /*<<< orphan*/  u8 ;
struct z_stream_s {unsigned int avail_in; unsigned int avail_out; unsigned int total_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
struct deflate_ctx {struct z_stream_s comp_stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int zlib_deflate (struct z_stream_s*,int /*<<< orphan*/ ) ; 
 int zlib_deflateReset (struct z_stream_s*) ; 

__attribute__((used)) static int __deflate_compress(const u8 *src, unsigned int slen,
			      u8 *dst, unsigned int *dlen, void *ctx)
{
	int ret = 0;
	struct deflate_ctx *dctx = ctx;
	struct z_stream_s *stream = &dctx->comp_stream;

	ret = zlib_deflateReset(stream);
	if (ret != Z_OK) {
		ret = -EINVAL;
		goto out;
	}

	stream->next_in = (u8 *)src;
	stream->avail_in = slen;
	stream->next_out = (u8 *)dst;
	stream->avail_out = *dlen;

	ret = zlib_deflate(stream, Z_FINISH);
	if (ret != Z_STREAM_END) {
		ret = -EINVAL;
		goto out;
	}
	ret = 0;
	*dlen = stream->total_out;
out:
	return ret;
}