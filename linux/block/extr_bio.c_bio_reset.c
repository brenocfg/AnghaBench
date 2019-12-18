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
struct bio {unsigned long bi_flags; int /*<<< orphan*/  __bi_remaining; } ;

/* Variables and functions */
 unsigned long BIO_RESET_BITS ; 
 int /*<<< orphan*/  BIO_RESET_BYTES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_uninit (struct bio*) ; 
 int /*<<< orphan*/  memset (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bio_reset(struct bio *bio)
{
	unsigned long flags = bio->bi_flags & (~0UL << BIO_RESET_BITS);

	bio_uninit(bio);

	memset(bio, 0, BIO_RESET_BYTES);
	bio->bi_flags = flags;
	atomic_set(&bio->__bi_remaining, 1);
}