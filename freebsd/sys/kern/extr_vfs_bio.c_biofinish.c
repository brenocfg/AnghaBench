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
struct devstat {int dummy; } ;
struct bio {int bio_error; int /*<<< orphan*/  bio_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  devstat_end_transaction_bio (struct devstat*,struct bio*) ; 

void
biofinish(struct bio *bp, struct devstat *stat, int error)
{
	
	if (error) {
		bp->bio_error = error;
		bp->bio_flags |= BIO_ERROR;
	}
	if (stat != NULL)
		devstat_end_transaction_bio(stat, bp);
	biodone(bp);
}