#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {size_t window_mask; int write_ptr; int last_write_ptr; int window_size; int cur_block_size; int block_parsing_finished; size_t solid_offset; int last_len; int const* dist_cache; int /*<<< orphan*/  rd; int /*<<< orphan*/  ldd; int /*<<< orphan*/  dd; scalar_t__* window_buf; int /*<<< orphan*/  ld; } ;
struct TYPE_3__ {int in_addr; scalar_t__ const bit_addr; } ;
struct compressed_block_header {int dummy; } ;
struct rar5 {TYPE_2__ cstate; TYPE_1__ bits; struct compressed_block_header last_block_hdr; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  size_t const int64_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int INT_MAX ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ bf_bit_size (struct compressed_block_header const*) ; 
 int copy_string (struct archive_read*,int,int const) ; 
 int decode_code_length (struct rar5*,scalar_t__ const*,int) ; 
 int decode_number (struct archive_read*,int /*<<< orphan*/ *,scalar_t__ const*,int*) ; 
 int /*<<< orphan*/  dist_cache_push (struct rar5*,int) ; 
 int dist_cache_touch (struct rar5*,int const) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int parse_filter (struct archive_read*,scalar_t__ const*) ; 
 int read_bits_32 (struct rar5*,scalar_t__ const*,int*) ; 
 int read_consume_bits (struct rar5*,scalar_t__ const*,int,int*) ; 
 int /*<<< orphan*/  skip_bits (struct rar5*,int) ; 

__attribute__((used)) static int do_uncompress_block(struct archive_read* a, const uint8_t* p) {
	struct rar5* rar = get_context(a);
	uint16_t num;
	int ret;

	const uint64_t cmask = rar->cstate.window_mask;
	const struct compressed_block_header* hdr = &rar->last_block_hdr;
	const uint8_t bit_size = 1 + bf_bit_size(hdr);

	while(1) {
		if(rar->cstate.write_ptr - rar->cstate.last_write_ptr >
		    (rar->cstate.window_size >> 1)) {
			/* Don't allow growing data by more than half of the
			 * window size at a time. In such case, break the loop;
			 *  next call to this function will continue processing
			 *  from this moment. */
			break;
		}

		if(rar->bits.in_addr > rar->cstate.cur_block_size - 1 ||
		    (rar->bits.in_addr == rar->cstate.cur_block_size - 1 &&
		    rar->bits.bit_addr >= bit_size))
		{
			/* If the program counter is here, it means the
			 * function has finished processing the block. */
			rar->cstate.block_parsing_finished = 1;
			break;
		}

		/* Decode the next literal. */
		if(ARCHIVE_OK != decode_number(a, &rar->cstate.ld, p, &num)) {
			return ARCHIVE_EOF;
		}

		/* Num holds a decompression literal, or 'command code'.
		 *
		 * - Values lower than 256 are just bytes. Those codes
		 *   can be stored in the output buffer directly.
		 *
		 * - Code 256 defines a new filter, which is later used to
		 *   ransform the data block accordingly to the filter type.
		 *   The data block needs to be fully uncompressed first.
		 *
		 * - Code bigger than 257 and smaller than 262 define
		 *   a repetition pattern that should be copied from
		 *   an already uncompressed chunk of data.
		 */

		if(num < 256) {
			/* Directly store the byte. */
			int64_t write_idx = rar->cstate.solid_offset +
			    rar->cstate.write_ptr++;

			rar->cstate.window_buf[write_idx & cmask] =
			    (uint8_t) num;
			continue;
		} else if(num >= 262) {
			uint16_t dist_slot;
			int len = decode_code_length(rar, p, num - 262),
				dbits,
				dist = 1;

			if(len == -1) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_PROGRAMMER,
				    "Failed to decode the code length");

				return ARCHIVE_FATAL;
			}

			if(ARCHIVE_OK != decode_number(a, &rar->cstate.dd, p,
			    &dist_slot))
			{
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_PROGRAMMER,
				    "Failed to decode the distance slot");

				return ARCHIVE_FATAL;
			}

			if(dist_slot < 4) {
				dbits = 0;
				dist += dist_slot;
			} else {
				dbits = dist_slot / 2 - 1;

				/* Cast to uint32_t will make sure the shift
				 * left operation won't produce undefined
				 * result. Then, the uint32_t type will
				 * be implicitly casted to int. */
				dist += (uint32_t) (2 |
				    (dist_slot & 1)) << dbits;
			}

			if(dbits > 0) {
				if(dbits >= 4) {
					uint32_t add = 0;
					uint16_t low_dist;

					if(dbits > 4) {
						if(ARCHIVE_OK != read_bits_32(
						    rar, p, &add)) {
							/* Return EOF if we
							 * can't read more
							 * data. */
							return ARCHIVE_EOF;
						}

						skip_bits(rar, dbits - 4);
						add = (add >> (
						    36 - dbits)) << 4;
						dist += add;
					}

					if(ARCHIVE_OK != decode_number(a,
					    &rar->cstate.ldd, p, &low_dist))
					{
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_PROGRAMMER,
						    "Failed to decode the "
						    "distance slot");

						return ARCHIVE_FATAL;
					}

					if(dist >= INT_MAX - low_dist - 1) {
						/* This only happens in
						 * invalid archives. */
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_FILE_FORMAT,
						    "Distance pointer "
						    "overflow");
						return ARCHIVE_FATAL;
					}

					dist += low_dist;
				} else {
					/* dbits is one of [0,1,2,3] */
					int add;

					if(ARCHIVE_OK != read_consume_bits(rar,
					     p, dbits, &add)) {
						/* Return EOF if we can't read
						 * more data. */
						return ARCHIVE_EOF;
					}

					dist += add;
				}
			}

			if(dist > 0x100) {
				len++;

				if(dist > 0x2000) {
					len++;

					if(dist > 0x40000) {
						len++;
					}
				}
			}

			dist_cache_push(rar, dist);
			rar->cstate.last_len = len;

			if(ARCHIVE_OK != copy_string(a, len, dist))
				return ARCHIVE_FATAL;

			continue;
		} else if(num == 256) {
			/* Create a filter. */
			ret = parse_filter(a, p);
			if(ret != ARCHIVE_OK)
				return ret;

			continue;
		} else if(num == 257) {
			if(rar->cstate.last_len != 0) {
				if(ARCHIVE_OK != copy_string(a,
				    rar->cstate.last_len,
				    rar->cstate.dist_cache[0]))
				{
					return ARCHIVE_FATAL;
				}
			}

			continue;
		} else if(num < 262) {
			const int idx = num - 258;
			const int dist = dist_cache_touch(rar, idx);

			uint16_t len_slot;
			int len;

			if(ARCHIVE_OK != decode_number(a, &rar->cstate.rd, p,
			    &len_slot)) {
				return ARCHIVE_FATAL;
			}

			len = decode_code_length(rar, p, len_slot);
			rar->cstate.last_len = len;

			if(ARCHIVE_OK != copy_string(a, len, dist))
				return ARCHIVE_FATAL;

			continue;
		}

		/* The program counter shouldn't reach here. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported block code: 0x%x", num);

		return ARCHIVE_FATAL;
	}

	return ARCHIVE_OK;
}