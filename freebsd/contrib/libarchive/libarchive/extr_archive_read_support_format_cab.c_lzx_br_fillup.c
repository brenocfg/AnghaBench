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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct lzx_stream {int avail_in; int /*<<< orphan*/ * next_in; } ;
struct lzx_br {int cache_avail; int cache_buffer; int have_odd; int /*<<< orphan*/  odd; } ;

/* Variables and functions */
 int CACHE_BITS ; 
 int archive_le16dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lzx_br_fillup(struct lzx_stream *strm, struct lzx_br *br)
{
/*
 * x86 processor family can read misaligned data without an access error.
 */
	int n = CACHE_BITS - br->cache_avail;

	for (;;) {
		switch (n >> 4) {
		case 4:
			if (strm->avail_in >= 8) {
				br->cache_buffer =
				    ((uint64_t)strm->next_in[1]) << 56 |
				    ((uint64_t)strm->next_in[0]) << 48 |
				    ((uint64_t)strm->next_in[3]) << 40 |
				    ((uint64_t)strm->next_in[2]) << 32 |
				    ((uint32_t)strm->next_in[5]) << 24 |
				    ((uint32_t)strm->next_in[4]) << 16 |
				    ((uint32_t)strm->next_in[7]) << 8 |
				     (uint32_t)strm->next_in[6];
				strm->next_in += 8;
				strm->avail_in -= 8;
				br->cache_avail += 8 * 8;
				return (1);
			}
			break;
		case 3:
			if (strm->avail_in >= 6) {
				br->cache_buffer =
		 		   (br->cache_buffer << 48) |
				    ((uint64_t)strm->next_in[1]) << 40 |
				    ((uint64_t)strm->next_in[0]) << 32 |
				    ((uint32_t)strm->next_in[3]) << 24 |
				    ((uint32_t)strm->next_in[2]) << 16 |
				    ((uint32_t)strm->next_in[5]) << 8 |
				     (uint32_t)strm->next_in[4];
				strm->next_in += 6;
				strm->avail_in -= 6;
				br->cache_avail += 6 * 8;
				return (1);
			}
			break;
		case 0:
			/* We have enough compressed data in
			 * the cache buffer.*/
			return (1);
		default:
			break;
		}
		if (strm->avail_in < 2) {
			/* There is not enough compressed data to
			 * fill up the cache buffer. */
			if (strm->avail_in == 1) {
				br->odd = *strm->next_in++;
				strm->avail_in--;
				br->have_odd = 1;
			}
			return (0);
		}
		br->cache_buffer =
		   (br->cache_buffer << 16) |
		    archive_le16dec(strm->next_in);
		strm->next_in += 2;
		strm->avail_in -= 2;
		br->cache_avail += 16;
		n -= 16;
	}
}