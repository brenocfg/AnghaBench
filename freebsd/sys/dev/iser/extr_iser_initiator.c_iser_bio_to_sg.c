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
struct scatterlist {int dummy; } ;
struct iser_data_buf {int size; struct scatterlist* sgl; } ;
struct bio {size_t bio_bcount; int bio_ma_offset; int /*<<< orphan*/ * bio_ma; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 size_t min (scalar_t__,size_t) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void
iser_bio_to_sg(struct bio *bp, struct iser_data_buf *data_buf)
{
	struct scatterlist *sg;
	int i;
	size_t len, tlen;
	int offset;

	tlen = bp->bio_bcount;
	offset = bp->bio_ma_offset;

	for (i = 0; 0 < tlen; i++, tlen -= len) {
		sg = &data_buf->sgl[i];
		len = min(PAGE_SIZE - offset, tlen);
		sg_set_page(sg, bp->bio_ma[i], len, offset);
		offset = 0;
	}

	data_buf->size = i;
	sg_mark_end(sg);
}