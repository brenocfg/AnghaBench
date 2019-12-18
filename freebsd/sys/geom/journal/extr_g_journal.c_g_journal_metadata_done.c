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
struct bio {scalar_t__ bio_error; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*,...) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  gj_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_journal_metadata_done(struct bio *bp)
{

	/*
	 * There is not much we can do on error except informing about it.
	 */
	if (bp->bio_error != 0) {
		GJ_LOGREQ(0, bp, "Cannot update metadata (error=%d).",
		    bp->bio_error);
	} else {
		GJ_LOGREQ(2, bp, "Metadata updated.");
	}
	gj_free(bp->bio_data, bp->bio_length);
	g_destroy_bio(bp);
}