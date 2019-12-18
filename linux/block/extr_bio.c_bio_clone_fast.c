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
struct bio_set {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __bio_clone_fast (struct bio*,struct bio*) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio_set*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int bio_integrity_clone (struct bio*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 

struct bio *bio_clone_fast(struct bio *bio, gfp_t gfp_mask, struct bio_set *bs)
{
	struct bio *b;

	b = bio_alloc_bioset(gfp_mask, 0, bs);
	if (!b)
		return NULL;

	__bio_clone_fast(b, bio);

	if (bio_integrity(bio)) {
		int ret;

		ret = bio_integrity_clone(b, bio, gfp_mask);

		if (ret < 0) {
			bio_put(b);
			return NULL;
		}
	}

	return b;
}