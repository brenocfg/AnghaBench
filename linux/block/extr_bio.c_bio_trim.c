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
struct TYPE_2__ {int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_advance (struct bio*,int) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_trim (struct bio*) ; 

void bio_trim(struct bio *bio, int offset, int size)
{
	/* 'bio' is a cloned bio which we need to trim to match
	 * the given offset and size.
	 */

	size <<= 9;
	if (offset == 0 && size == bio->bi_iter.bi_size)
		return;

	bio_advance(bio, offset << 9);
	bio->bi_iter.bi_size = size;

	if (bio_integrity(bio))
		bio_integrity_trim(bio);

}