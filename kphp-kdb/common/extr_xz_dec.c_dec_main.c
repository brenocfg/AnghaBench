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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int size; int /*<<< orphan*/  pos; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  hash; } ;
struct TYPE_6__ {int compressed; int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {int size; } ;
struct xz_dec {size_t in_start; int sequence; TYPE_4__ temp; TYPE_3__ index; TYPE_2__ block; int /*<<< orphan*/  check_type; TYPE_1__ block_header; } ;
struct xz_buf {size_t in_pos; size_t in_size; int /*<<< orphan*/ * in; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
#define  SEQ_BLOCK_CHECK 137 
#define  SEQ_BLOCK_HEADER 136 
#define  SEQ_BLOCK_PADDING 135 
#define  SEQ_BLOCK_START 134 
#define  SEQ_BLOCK_UNCOMPRESS 133 
#define  SEQ_INDEX 132 
#define  SEQ_INDEX_CRC32 131 
#define  SEQ_INDEX_PADDING 130 
#define  SEQ_STREAM_FOOTER 129 
#define  SEQ_STREAM_HEADER 128 
 int STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  XZ_CHECK_CRC32 ; 
 int XZ_DATA_ERROR ; 
 int XZ_OK ; 
 int XZ_STREAM_END ; 
 int crc32_validate (struct xz_dec*,struct xz_buf*) ; 
 int dec_block (struct xz_dec*,struct xz_buf*) ; 
 int dec_block_header (struct xz_dec*) ; 
 int dec_index (struct xz_dec*,struct xz_buf*) ; 
 int dec_stream_footer (struct xz_dec*) ; 
 int dec_stream_header (struct xz_dec*) ; 
 int /*<<< orphan*/  fill_temp (struct xz_dec*,struct xz_buf*) ; 
 int /*<<< orphan*/  index_update (struct xz_dec*,struct xz_buf*) ; 
 int /*<<< orphan*/  memeq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum xz_ret dec_main(struct xz_dec *s, struct xz_buf *b)
{
	enum xz_ret ret;

	/*
	 * Store the start position for the case when we are in the middle
	 * of the Index field.
	 */
	s->in_start = b->in_pos;

	while (1) {
		switch (s->sequence) {
		case SEQ_STREAM_HEADER:
			/*
			 * Stream Header is copied to s->temp, and then
			 * decoded from there. This way if the caller
			 * gives us only little input at a time, we can
			 * still keep the Stream Header decoding code
			 * simple. Similar approach is used in many places
			 * in this file.
			 */
			if (!fill_temp(s, b))
				return XZ_OK;

			/*
			 * If dec_stream_header() returns
			 * XZ_UNSUPPORTED_CHECK, it is still possible
			 * to continue decoding if working in multi-call
			 * mode. Thus, update s->sequence before calling
			 * dec_stream_header().
			 */
			s->sequence = SEQ_BLOCK_START;

			ret = dec_stream_header(s);
			if (ret != XZ_OK)
				return ret;

		case SEQ_BLOCK_START:
			/* We need one byte of input to continue. */
			if (b->in_pos == b->in_size)
				return XZ_OK;

			/* See if this is the beginning of the Index field. */
			if (b->in[b->in_pos] == 0) {
				s->in_start = b->in_pos++;
				s->sequence = SEQ_INDEX;
				break;
			}

			/*
			 * Calculate the size of the Block Header and
			 * prepare to decode it.
			 */
			s->block_header.size
				= ((uint32_t)b->in[b->in_pos] + 1) * 4;

			s->temp.size = s->block_header.size;
			s->temp.pos = 0;
			s->sequence = SEQ_BLOCK_HEADER;

		case SEQ_BLOCK_HEADER:
			if (!fill_temp(s, b))
				return XZ_OK;

			ret = dec_block_header(s);
			if (ret != XZ_OK)
				return ret;

			s->sequence = SEQ_BLOCK_UNCOMPRESS;

		case SEQ_BLOCK_UNCOMPRESS:
			ret = dec_block(s, b);
			if (ret != XZ_STREAM_END)
				return ret;

			s->sequence = SEQ_BLOCK_PADDING;

		case SEQ_BLOCK_PADDING:
			/*
			 * Size of Compressed Data + Block Padding
			 * must be a multiple of four. We don't need
			 * s->block.compressed for anything else
			 * anymore, so we use it here to test the size
			 * of the Block Padding field.
			 */
			while (s->block.compressed & 3) {
				if (b->in_pos == b->in_size)
					return XZ_OK;

				if (b->in[b->in_pos++] != 0)
					return XZ_DATA_ERROR;

				++s->block.compressed;
			}

			s->sequence = SEQ_BLOCK_CHECK;

		case SEQ_BLOCK_CHECK:
			if (s->check_type == XZ_CHECK_CRC32) {
				ret = crc32_validate(s, b);
				if (ret != XZ_STREAM_END)
					return ret;
			}

			s->sequence = SEQ_BLOCK_START;
			break;

		case SEQ_INDEX:
			ret = dec_index(s, b);
			if (ret != XZ_STREAM_END)
				return ret;

			s->sequence = SEQ_INDEX_PADDING;

		case SEQ_INDEX_PADDING:
			while ((s->index.size + (b->in_pos - s->in_start))
					& 3) {
				if (b->in_pos == b->in_size) {
					index_update(s, b);
					return XZ_OK;
				}

				if (b->in[b->in_pos++] != 0)
					return XZ_DATA_ERROR;
			}

			/* Finish the CRC32 value and Index size. */
			index_update(s, b);

			/* Compare the hashes to validate the Index field. */
			if (!memeq(&s->block.hash, &s->index.hash,
					sizeof(s->block.hash)))
				return XZ_DATA_ERROR;

			s->sequence = SEQ_INDEX_CRC32;

		case SEQ_INDEX_CRC32:
			ret = crc32_validate(s, b);
			if (ret != XZ_STREAM_END)
				return ret;

			s->temp.size = STREAM_HEADER_SIZE;
			s->sequence = SEQ_STREAM_FOOTER;

		case SEQ_STREAM_FOOTER:
			if (!fill_temp(s, b))
				return XZ_OK;

			return dec_stream_footer(s);
		}
	}

	/* Never reached */
}