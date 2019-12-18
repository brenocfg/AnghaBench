#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_8__ {scalar_t__ switch_multivolume; scalar_t__ cur_block_size; scalar_t__ block_parsing_finished; int /*<<< orphan*/  const* block_buf; } ;
struct TYPE_7__ {scalar_t__ bytes_remaining; } ;
struct TYPE_6__ {scalar_t__ bit_addr; scalar_t__ in_addr; } ;
struct TYPE_5__ {scalar_t__ volume; } ;
struct rar5 {TYPE_4__ cstate; TYPE_3__ file; int /*<<< orphan*/  last_block_hdr; TYPE_2__ bits; TYPE_1__ main; } ;
struct compressed_block_header {int dummy; } ;
struct archive_read {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int advance_multivolume (struct archive_read*) ; 
 scalar_t__ bf_byte_count (int /*<<< orphan*/ *) ; 
 scalar_t__ bf_is_table_present (int /*<<< orphan*/ *) ; 
 int consume (struct archive_read*,scalar_t__) ; 
 int do_uncompress_block (struct archive_read*,int /*<<< orphan*/  const*) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int merge_block (struct archive_read*,scalar_t__,int /*<<< orphan*/  const**) ; 
 int parse_block_header (struct archive_read*,int /*<<< orphan*/  const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int parse_tables (struct archive_read*,struct rar5*,int /*<<< orphan*/  const*) ; 
 scalar_t__ rar5_min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_ahead (struct archive_read*,int,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int process_block(struct archive_read* a) {
	const uint8_t* p;
	struct rar5* rar = get_context(a);
	int ret;

	/* If we don't have any data to be processed, this most probably means
	 * we need to switch to the next volume. */
	if(rar->main.volume && rar->file.bytes_remaining == 0) {
		ret = advance_multivolume(a);
		if(ret != ARCHIVE_OK)
			return ret;
	}

	if(rar->cstate.block_parsing_finished) {
		ssize_t block_size;

		/* The header size won't be bigger than 6 bytes. */
		if(!read_ahead(a, 6, &p)) {
			/* Failed to prefetch data block header. */
			return ARCHIVE_EOF;
		}

		/*
		 * Read block_size by parsing block header. Validate the header
		 * by calculating CRC byte stored inside the header. Size of
		 * the header is not constant (block size can be stored either
		 * in 1 or 2 bytes), that's why block size is left out from the
		 * `compressed_block_header` structure and returned by
		 * `parse_block_header` as the second argument. */

		ret = parse_block_header(a, p, &block_size,
		    &rar->last_block_hdr);
		if(ret != ARCHIVE_OK) {
			return ret;
		}

		/* Skip block header. Next data is huffman tables,
		 * if present. */
		ssize_t to_skip = sizeof(struct compressed_block_header) +
			bf_byte_count(&rar->last_block_hdr) + 1;

		if(ARCHIVE_OK != consume(a, to_skip))
			return ARCHIVE_EOF;

		rar->file.bytes_remaining -= to_skip;

		/* The block size gives information about the whole block size,
		 * but the block could be stored in split form when using
		 * multi-volume archives. In this case, the block size will be
		 * bigger than the actual data stored in this file. Remaining
		 * part of the data will be in another file. */

		ssize_t cur_block_size =
			rar5_min(rar->file.bytes_remaining, block_size);

		if(block_size > rar->file.bytes_remaining) {
			/* If current blocks' size is bigger than our data
			 * size, this means we have a multivolume archive.
			 * In this case, skip all base headers until the end
			 * of the file, proceed to next "partXXX.rar" volume,
			 * find its signature, skip all headers up to the first
			 * FILE base header, and continue from there.
			 *
			 * Note that `merge_block` will update the `rar`
			 * context structure quite extensively. */

			ret = merge_block(a, block_size, &p);
			if(ret != ARCHIVE_OK) {
				return ret;
			}

			cur_block_size = block_size;

			/* Current stream pointer should be now directly
			 * *after* the block that spanned through multiple
			 * archive files. `p` pointer should have the data of
			 * the *whole* block (merged from partial blocks
			 * stored in multiple archives files). */
		} else {
			rar->cstate.switch_multivolume = 0;

			/* Read the whole block size into memory. This can take
			 * up to  8 megabytes of memory in theoretical cases.
			 * Might be worth to optimize this and use a standard
			 * chunk of 4kb's. */
			if(!read_ahead(a, 4 + cur_block_size, &p)) {
				/* Failed to prefetch block data. */
				return ARCHIVE_EOF;
			}
		}

		rar->cstate.block_buf = p;
		rar->cstate.cur_block_size = cur_block_size;
		rar->cstate.block_parsing_finished = 0;

		rar->bits.in_addr = 0;
		rar->bits.bit_addr = 0;

		if(bf_is_table_present(&rar->last_block_hdr)) {
			/* Load Huffman tables. */
			ret = parse_tables(a, rar, p);
			if(ret != ARCHIVE_OK) {
				/* Error during decompression of Huffman
				 * tables. */
				return ret;
			}
		}
	} else {
		/* Block parsing not finished, reuse previous memory buffer. */
		p = rar->cstate.block_buf;
	}

	/* Uncompress the block, or a part of it, depending on how many bytes
	 * will be generated by uncompressing the block.
	 *
	 * In case too many bytes will be generated, calling this function
	 * again will resume the uncompression operation. */
	ret = do_uncompress_block(a, p);
	if(ret != ARCHIVE_OK) {
		return ret;
	}

	if(rar->cstate.block_parsing_finished &&
	    rar->cstate.switch_multivolume == 0 &&
	    rar->cstate.cur_block_size > 0)
	{
		/* If we're processing a normal block, consume the whole
		 * block. We can do this because we've already read the whole
		 * block to memory. */
		if(ARCHIVE_OK != consume(a, rar->cstate.cur_block_size))
			return ARCHIVE_FATAL;

		rar->file.bytes_remaining -= rar->cstate.cur_block_size;
	} else if(rar->cstate.switch_multivolume) {
		/* Don't consume the block if we're doing multivolume
		 * processing. The volume switching function will consume
		 * the proper count of bytes instead. */
		rar->cstate.switch_multivolume = 0;
	}

	return ARCHIVE_OK;
}