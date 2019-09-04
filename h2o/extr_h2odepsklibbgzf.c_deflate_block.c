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
struct TYPE_7__ {int avail_in; int avail_out; int total_out; void* next_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * zfree; int /*<<< orphan*/ * zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int block_offset; int /*<<< orphan*/ * uncompressed_block; int /*<<< orphan*/  errcode; int /*<<< orphan*/  compress_level; int /*<<< orphan*/ * compressed_block; } ;
typedef  TYPE_2__ BGZF ;

/* Variables and functions */
 int BGZF_BLOCK_SIZE ; 
 int /*<<< orphan*/  BGZF_ERR_ZLIB ; 
 int BLOCK_FOOTER_LENGTH ; 
 size_t BLOCK_HEADER_LENGTH ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int crc32 (int,int /*<<< orphan*/ *,int) ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (TYPE_1__*) ; 
 int deflateInit2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_magic ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  packInt16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  packInt32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int deflate_block(BGZF *fp, int block_length)
{
	uint8_t *buffer = fp->compressed_block;
	int buffer_size = BGZF_BLOCK_SIZE;
	int input_length = block_length;
	int compressed_length = 0;
	int remaining;
	uint32_t crc;

	assert(block_length <= BGZF_BLOCK_SIZE); // guaranteed by the caller
	memcpy(buffer, g_magic, BLOCK_HEADER_LENGTH); // the last two bytes are a place holder for the length of the block
	while (1) { // loop to retry for blocks that do not compress enough
		int status;
		z_stream zs;
		zs.zalloc = NULL;
		zs.zfree = NULL;
		zs.next_in = fp->uncompressed_block;
		zs.avail_in = input_length;
		zs.next_out = (void*)&buffer[BLOCK_HEADER_LENGTH];
		zs.avail_out = buffer_size - BLOCK_HEADER_LENGTH - BLOCK_FOOTER_LENGTH;
		status = deflateInit2(&zs, fp->compress_level, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY); // -15 to disable zlib header/footer
		if (status != Z_OK) {
			fp->errcode |= BGZF_ERR_ZLIB;
			return -1;
		}
		status = deflate(&zs, Z_FINISH);
		if (status != Z_STREAM_END) { // not compressed enough
			deflateEnd(&zs); // reset the stream
			if (status == Z_OK) { // reduce the size and recompress
				input_length -= 1024;
				assert(input_length > 0); // logically, this should not happen
				continue;
			}
			fp->errcode |= BGZF_ERR_ZLIB;
			return -1;
		}
		if (deflateEnd(&zs) != Z_OK) {
			fp->errcode |= BGZF_ERR_ZLIB;
			return -1;
		}
		compressed_length = zs.total_out;
		compressed_length += BLOCK_HEADER_LENGTH + BLOCK_FOOTER_LENGTH;
		assert(compressed_length <= BGZF_BLOCK_SIZE);
		break;
	}

	assert(compressed_length > 0);
	packInt16((uint8_t*)&buffer[16], compressed_length - 1); // write the compressed_length; -1 to fit 2 bytes
	crc = crc32(0L, NULL, 0L);
	crc = crc32(crc, fp->uncompressed_block, input_length);
	packInt32((uint8_t*)&buffer[compressed_length-8], crc);
	packInt32((uint8_t*)&buffer[compressed_length-4], input_length);

	remaining = block_length - input_length;
	if (remaining > 0) {
		assert(remaining <= input_length);
		memcpy(fp->uncompressed_block, fp->uncompressed_block + input_length, remaining);
	}
	fp->block_offset = remaining;
	return compressed_length;
}