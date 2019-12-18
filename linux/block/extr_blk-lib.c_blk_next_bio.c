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
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct bio* bio_alloc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

struct bio *blk_next_bio(struct bio *bio, unsigned int nr_pages, gfp_t gfp)
{
	struct bio *new = bio_alloc(gfp, nr_pages);

	if (bio) {
		bio_chain(bio, new);
		submit_bio(bio);
	}

	return new;
}