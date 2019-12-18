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
struct iov_iter {int dummy; } ;
struct bio {scalar_t__ bi_vcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NO_PAGE_REF ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (scalar_t__) ; 
 int __bio_iov_bvec_add_pages (struct bio*,struct iov_iter*) ; 
 int __bio_iov_iter_get_pages (struct bio*,struct iov_iter*) ; 
 int /*<<< orphan*/  bio_full (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int iov_iter_is_bvec (struct iov_iter*) ; 

int bio_iov_iter_get_pages(struct bio *bio, struct iov_iter *iter)
{
	const bool is_bvec = iov_iter_is_bvec(iter);
	int ret;

	if (WARN_ON_ONCE(bio->bi_vcnt))
		return -EINVAL;

	do {
		if (is_bvec)
			ret = __bio_iov_bvec_add_pages(bio, iter);
		else
			ret = __bio_iov_iter_get_pages(bio, iter);
	} while (!ret && iov_iter_count(iter) && !bio_full(bio, 0));

	if (is_bvec)
		bio_set_flag(bio, BIO_NO_PAGE_REF);
	return bio->bi_vcnt ? 0 : ret;
}