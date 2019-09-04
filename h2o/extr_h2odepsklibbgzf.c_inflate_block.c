#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int avail_in; int total_out; int /*<<< orphan*/  avail_out; int /*<<< orphan*/  next_out; scalar_t__ next_in; int /*<<< orphan*/ * zfree; int /*<<< orphan*/ * zalloc; } ;
typedef  TYPE_1__ z_stream ;
struct TYPE_8__ {int /*<<< orphan*/  errcode; int /*<<< orphan*/  uncompressed_block; scalar_t__ compressed_block; } ;
typedef  TYPE_2__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_BLOCK_SIZE ; 
 int /*<<< orphan*/  BGZF_ERR_ZLIB ; 
 int /*<<< orphan*/  Z_FINISH ; 
 scalar_t__ Z_OK ; 
 scalar_t__ Z_STREAM_END ; 
 scalar_t__ inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ inflateEnd (TYPE_1__*) ; 
 scalar_t__ inflateInit2 (TYPE_1__*,int) ; 

__attribute__((used)) static int inflate_block(BGZF* fp, int block_length)
{
	z_stream zs;
	zs.zalloc = NULL;
	zs.zfree = NULL;
	zs.next_in = fp->compressed_block + 18;
	zs.avail_in = block_length - 16;
	zs.next_out = fp->uncompressed_block;
	zs.avail_out = BGZF_BLOCK_SIZE;

	if (inflateInit2(&zs, -15) != Z_OK) {
		fp->errcode |= BGZF_ERR_ZLIB;
		return -1;
	}
	if (inflate(&zs, Z_FINISH) != Z_STREAM_END) {
		inflateEnd(&zs);
		fp->errcode |= BGZF_ERR_ZLIB;
		return -1;
	}
	if (inflateEnd(&zs) != Z_OK) {
		fp->errcode |= BGZF_ERR_ZLIB;
		return -1;
	}
	return zs.total_out;
}