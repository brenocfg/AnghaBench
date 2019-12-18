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
struct rq_map_data {int offset; int page_order; int nr_entries; scalar_t__ null_mapped; scalar_t__ from_user; struct page** pages; } ;
struct request_queue {int bounce_gfp; } ;
struct page {int dummy; } ;
struct iov_iter {unsigned int count; } ;
struct bio_map_data {int is_our_pages; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {struct bio_map_data* bi_private; TYPE_1__ bi_iter; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int BIO_MAX_PAGES ; 
 int /*<<< orphan*/  BIO_NULL_MAPPED ; 
 int DIV_ROUND_UP (unsigned int,int) ; 
 int ENOMEM ; 
 struct bio* ERR_PTR (int) ; 
 int PAGE_SIZE ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 unsigned int bio_add_pc_page (struct request_queue*,struct bio*,struct page*,unsigned int,unsigned int) ; 
 struct bio_map_data* bio_alloc_map_data (struct iov_iter*,int) ; 
 int bio_copy_from_iter (struct bio*,struct iov_iter*) ; 
 int /*<<< orphan*/  bio_free_pages (struct bio*) ; 
 struct bio* bio_kmalloc (int,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,scalar_t__) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct bio_map_data*) ; 
 unsigned int offset_in_page (int) ; 
 int /*<<< orphan*/  zero_fill_bio (struct bio*) ; 

struct bio *bio_copy_user_iov(struct request_queue *q,
			      struct rq_map_data *map_data,
			      struct iov_iter *iter,
			      gfp_t gfp_mask)
{
	struct bio_map_data *bmd;
	struct page *page;
	struct bio *bio;
	int i = 0, ret;
	int nr_pages;
	unsigned int len = iter->count;
	unsigned int offset = map_data ? offset_in_page(map_data->offset) : 0;

	bmd = bio_alloc_map_data(iter, gfp_mask);
	if (!bmd)
		return ERR_PTR(-ENOMEM);

	/*
	 * We need to do a deep copy of the iov_iter including the iovecs.
	 * The caller provided iov might point to an on-stack or otherwise
	 * shortlived one.
	 */
	bmd->is_our_pages = map_data ? 0 : 1;

	nr_pages = DIV_ROUND_UP(offset + len, PAGE_SIZE);
	if (nr_pages > BIO_MAX_PAGES)
		nr_pages = BIO_MAX_PAGES;

	ret = -ENOMEM;
	bio = bio_kmalloc(gfp_mask, nr_pages);
	if (!bio)
		goto out_bmd;

	ret = 0;

	if (map_data) {
		nr_pages = 1 << map_data->page_order;
		i = map_data->offset / PAGE_SIZE;
	}
	while (len) {
		unsigned int bytes = PAGE_SIZE;

		bytes -= offset;

		if (bytes > len)
			bytes = len;

		if (map_data) {
			if (i == map_data->nr_entries * nr_pages) {
				ret = -ENOMEM;
				break;
			}

			page = map_data->pages[i / nr_pages];
			page += (i % nr_pages);

			i++;
		} else {
			page = alloc_page(q->bounce_gfp | gfp_mask);
			if (!page) {
				ret = -ENOMEM;
				break;
			}
		}

		if (bio_add_pc_page(q, bio, page, bytes, offset) < bytes) {
			if (!map_data)
				__free_page(page);
			break;
		}

		len -= bytes;
		offset = 0;
	}

	if (ret)
		goto cleanup;

	if (map_data)
		map_data->offset += bio->bi_iter.bi_size;

	/*
	 * success
	 */
	if ((iov_iter_rw(iter) == WRITE && (!map_data || !map_data->null_mapped)) ||
	    (map_data && map_data->from_user)) {
		ret = bio_copy_from_iter(bio, iter);
		if (ret)
			goto cleanup;
	} else {
		if (bmd->is_our_pages)
			zero_fill_bio(bio);
		iov_iter_advance(iter, bio->bi_iter.bi_size);
	}

	bio->bi_private = bmd;
	if (map_data && map_data->null_mapped)
		bio_set_flag(bio, BIO_NULL_MAPPED);
	return bio;
cleanup:
	if (!map_data)
		bio_free_pages(bio);
	bio_put(bio);
out_bmd:
	kfree(bmd);
	return ERR_PTR(ret);
}