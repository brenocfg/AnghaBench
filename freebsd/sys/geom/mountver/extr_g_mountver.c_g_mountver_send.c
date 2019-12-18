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
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct bio {int /*<<< orphan*/  bio_done; TYPE_1__* bio_to; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mountver_done ; 

__attribute__((used)) static void
g_mountver_send(struct bio *bp)
{
	struct g_geom *gp;
	struct bio *cbp;

	gp = bp->bio_to->geom;

	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}

	cbp->bio_done = g_mountver_done;
	g_io_request(cbp, LIST_FIRST(&gp->consumer));
}