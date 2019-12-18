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
typedef  int uint16_t ;
struct lzx_stream {scalar_t__ avail_in; scalar_t__* next_in; } ;
struct lzx_br {int cache_avail; int cache_buffer; int odd; scalar_t__ have_odd; } ;

/* Variables and functions */
 int CACHE_BITS ; 

__attribute__((used)) static void
lzx_br_fixup(struct lzx_stream *strm, struct lzx_br *br)
{
	int n = CACHE_BITS - br->cache_avail;

	if (br->have_odd && n >= 16 && strm->avail_in > 0) {
		br->cache_buffer =
		   (br->cache_buffer << 16) |
		   ((uint16_t)(*strm->next_in)) << 8 | br->odd;
		strm->next_in++;
		strm->avail_in--;
		br->cache_avail += 16;
		br->have_odd = 0;
	}
}