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
struct bio {scalar_t__ bio_error; scalar_t__ bio_inbed; scalar_t__ bio_children; scalar_t__ bio_completed; struct bio* bio_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 

void
g_std_done(struct bio *bp)
{
	struct bio *bp2;

	bp2 = bp->bio_parent;
	if (bp2->bio_error == 0)
		bp2->bio_error = bp->bio_error;
	bp2->bio_completed += bp->bio_completed;
	g_destroy_bio(bp);
	bp2->bio_inbed++;
	if (bp2->bio_children == bp2->bio_inbed)
		g_io_deliver(bp2, bp2->bio_error);
}