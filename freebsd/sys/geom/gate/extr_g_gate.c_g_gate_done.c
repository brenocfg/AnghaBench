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
struct bio {scalar_t__ bio_error; int /*<<< orphan*/  bio_children; int /*<<< orphan*/  bio_inbed; int /*<<< orphan*/  bio_completed; struct bio* bio_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_gate_queue_io (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_gate_done(struct bio *cbp)
{
	struct bio *pbp;

	pbp = cbp->bio_parent;
	if (cbp->bio_error == 0) {
		pbp->bio_completed = cbp->bio_completed;
		g_destroy_bio(cbp);
		pbp->bio_inbed++;
		g_io_deliver(pbp, 0);
	} else {
		/* If direct read failed, pass it through userland daemon. */
		g_destroy_bio(cbp);
		pbp->bio_children--;
		g_gate_queue_io(pbp);
	}
}