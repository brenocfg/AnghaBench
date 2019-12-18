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
struct TYPE_2__ {scalar_t__ max_write_zeroes_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;
struct bio_set {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 struct bio* bio_split (struct bio*,scalar_t__,int /*<<< orphan*/ ,struct bio_set*) ; 

__attribute__((used)) static struct bio *blk_bio_write_zeroes_split(struct request_queue *q,
		struct bio *bio, struct bio_set *bs, unsigned *nsegs)
{
	*nsegs = 0;

	if (!q->limits.max_write_zeroes_sectors)
		return NULL;

	if (bio_sectors(bio) <= q->limits.max_write_zeroes_sectors)
		return NULL;

	return bio_split(bio, q->limits.max_write_zeroes_sectors, GFP_NOIO, bs);
}