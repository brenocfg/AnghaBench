#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_offset; unsigned int bv_len; struct page* bv_page; } ;
struct TYPE_2__ {unsigned int bi_size; } ;
struct bio {size_t bi_vcnt; TYPE_1__ bi_iter; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  BIO_WORKINGSET ; 
 int /*<<< orphan*/  PageWorkingset (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_full (struct bio*,unsigned int) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __bio_add_page(struct bio *bio, struct page *page,
		unsigned int len, unsigned int off)
{
	struct bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt];

	WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED));
	WARN_ON_ONCE(bio_full(bio, len));

	bv->bv_page = page;
	bv->bv_offset = off;
	bv->bv_len = len;

	bio->bi_iter.bi_size += len;
	bio->bi_vcnt++;

	if (!bio_flagged(bio, BIO_WORKINGSET) && unlikely(PageWorkingset(page)))
		bio_set_flag(bio, BIO_WORKINGSET);
}