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
struct lzh_stream {struct lzh_dec* ds; } ;
struct TYPE_4__ {int len_bits; } ;
struct TYPE_3__ {scalar_t__ cache_avail; scalar_t__ cache_buffer; } ;
struct lzh_dec {int error; unsigned int w_size; int w_mask; int pos_pt_len_size; int pos_pt_len_bits; int literal_pt_len_bits; TYPE_2__ pt; TYPE_2__ lt; TYPE_1__ br; int /*<<< orphan*/  literal_pt_len_size; scalar_t__ state; scalar_t__ w_pos; int /*<<< orphan*/ * w_buff; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  LT_BITLEN_SIZE ; 
 int /*<<< orphan*/  PT_BITLEN_SIZE ; 
 struct lzh_dec* calloc (int,int) ; 
 scalar_t__ lzh_huffman_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
lzh_decode_init(struct lzh_stream *strm, const char *method)
{
	struct lzh_dec *ds;
	int w_bits, w_size;

	if (strm->ds == NULL) {
		strm->ds = calloc(1, sizeof(*strm->ds));
		if (strm->ds == NULL)
			return (ARCHIVE_FATAL);
	}
	ds = strm->ds;
	ds->error = ARCHIVE_FAILED;
	if (method == NULL || method[0] != 'l' || method[1] != 'h')
		return (ARCHIVE_FAILED);
	switch (method[2]) {
	case '5':
		w_bits = 13;/* 8KiB for window */
		break;
	case '6':
		w_bits = 15;/* 32KiB for window */
		break;
	case '7':
		w_bits = 16;/* 64KiB for window */
		break;
	default:
		return (ARCHIVE_FAILED);/* Not supported. */
	}
	ds->error = ARCHIVE_FATAL;
	/* Expand a window size up to 128 KiB for decompressing process
	 * performance whatever its original window size is. */
	ds->w_size = 1U << 17;
	ds->w_mask = ds->w_size -1;
	if (ds->w_buff == NULL) {
		ds->w_buff = malloc(ds->w_size);
		if (ds->w_buff == NULL)
			return (ARCHIVE_FATAL);
	}
	w_size = 1U << w_bits;
	memset(ds->w_buff + ds->w_size - w_size, 0x20, w_size);
	ds->w_pos = 0;
	ds->state = 0;
	ds->pos_pt_len_size = w_bits + 1;
	ds->pos_pt_len_bits = (w_bits == 15 || w_bits == 16)? 5: 4;
	ds->literal_pt_len_size = PT_BITLEN_SIZE;
	ds->literal_pt_len_bits = 5;
	ds->br.cache_buffer = 0;
	ds->br.cache_avail = 0;

	if (lzh_huffman_init(&(ds->lt), LT_BITLEN_SIZE, 16)
	    != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	ds->lt.len_bits = 9;
	if (lzh_huffman_init(&(ds->pt), PT_BITLEN_SIZE, 16)
	    != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	ds->error = 0;

	return (ARCHIVE_OK);
}