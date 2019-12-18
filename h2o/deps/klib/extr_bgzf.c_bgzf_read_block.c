#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  _bgzf_file_t ;
struct TYPE_6__ {int block_length; int /*<<< orphan*/  block_address; scalar_t__ block_offset; int /*<<< orphan*/  errcode; scalar_t__ fp; scalar_t__ compressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_ERR_HEADER ; 
 int /*<<< orphan*/  BGZF_ERR_IO ; 
 int BLOCK_HEADER_LENGTH ; 
 int _bgzf_read (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _bgzf_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_block (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check_header (int /*<<< orphan*/ *) ; 
 int inflate_block (TYPE_1__*,int) ; 
 scalar_t__ load_block_from_cache (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int unpackInt16 (int /*<<< orphan*/ *) ; 

int bgzf_read_block(BGZF *fp)
{
	uint8_t header[BLOCK_HEADER_LENGTH], *compressed_block;
	int count, size = 0, block_length, remaining;
	int64_t block_address;
	block_address = _bgzf_tell((_bgzf_file_t)fp->fp);
	if (load_block_from_cache(fp, block_address)) return 0;
	count = _bgzf_read(fp->fp, header, sizeof(header));
	if (count == 0) { // no data read
		fp->block_length = 0;
		return 0;
	}
	if (count != sizeof(header) || !check_header(header)) {
		fp->errcode |= BGZF_ERR_HEADER;
		return -1;
	}
	size = count;
	block_length = unpackInt16((uint8_t*)&header[16]) + 1; // +1 because when writing this number, we used "-1"
	compressed_block = (uint8_t*)fp->compressed_block;
	memcpy(compressed_block, header, BLOCK_HEADER_LENGTH);
	remaining = block_length - BLOCK_HEADER_LENGTH;
	count = _bgzf_read(fp->fp, &compressed_block[BLOCK_HEADER_LENGTH], remaining);
	if (count != remaining) {
		fp->errcode |= BGZF_ERR_IO;
		return -1;
	}
	size += count;
	if ((count = inflate_block(fp, block_length)) < 0) return -1;
	if (fp->block_length != 0) fp->block_offset = 0; // Do not reset offset if this read follows a seek.
	fp->block_address = block_address;
	fp->block_length = count;
	cache_block(fp, size);
	return 0;
}