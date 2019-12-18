#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ unpadded; scalar_t__ uncompressed; int /*<<< orphan*/  crc32; } ;
struct TYPE_6__ {scalar_t__ count; int sequence; TYPE_2__ hash; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct xz_dec {scalar_t__ vli; TYPE_3__ index; TYPE_1__ block; } ;
struct xz_buf {int /*<<< orphan*/  in_size; int /*<<< orphan*/  in_pos; int /*<<< orphan*/  in; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
#define  SEQ_INDEX_COUNT 130 
#define  SEQ_INDEX_UNCOMPRESSED 129 
#define  SEQ_INDEX_UNPADDED 128 
 int XZ_DATA_ERROR ; 
 int XZ_STREAM_END ; 
 int dec_vli (struct xz_dec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_update (struct xz_dec*,struct xz_buf*) ; 
 int /*<<< orphan*/  xz_crc32 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum xz_ret dec_index(struct xz_dec *s, struct xz_buf *b)
{
	enum xz_ret ret;

	do {
		ret = dec_vli(s, b->in, &b->in_pos, b->in_size);
		if (ret != XZ_STREAM_END) {
			index_update(s, b);
			return ret;
		}

		switch (s->index.sequence) {
		case SEQ_INDEX_COUNT:
			s->index.count = s->vli;

			/*
			 * Validate that the Number of Records field
			 * indicates the same number of Records as
			 * there were Blocks in the Stream.
			 */
			if (s->index.count != s->block.count)
				return XZ_DATA_ERROR;

			s->index.sequence = SEQ_INDEX_UNPADDED;
			break;

		case SEQ_INDEX_UNPADDED:
			s->index.hash.unpadded += s->vli;
			s->index.sequence = SEQ_INDEX_UNCOMPRESSED;
			break;

		case SEQ_INDEX_UNCOMPRESSED:
			s->index.hash.uncompressed += s->vli;
			s->index.hash.crc32 = xz_crc32(
					(const uint8_t *)&s->index.hash,
					sizeof(s->index.hash),
					s->index.hash.crc32);
			--s->index.count;
			s->index.sequence = SEQ_INDEX_UNPADDED;
			break;
		}
	} while (s->index.count > 0);

	return XZ_STREAM_END;
}