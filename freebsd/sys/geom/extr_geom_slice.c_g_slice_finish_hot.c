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
struct g_slicer {struct g_slice* slices; } ;
struct g_slice {scalar_t__ length; scalar_t__ offset; } ;
struct g_geom {int /*<<< orphan*/  consumer; struct g_slicer* softc; } ;
struct g_consumer {int dummy; } ;
struct bio {scalar_t__ bio_offset; scalar_t__ bio_length; int /*<<< orphan*/  bio_done; TYPE_1__* bio_to; int /*<<< orphan*/ * bio_from; } ;
struct TYPE_2__ {int index; struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_std_done ; 

void
g_slice_finish_hot(struct bio *bp)
{
	struct bio *bp2;
	struct g_geom *gp;
	struct g_consumer *cp;
	struct g_slicer *gsp;
	struct g_slice *gsl;
	int idx;

	KASSERT(bp->bio_to != NULL,
	    ("NULL bio_to in g_slice_finish_hot(%p)", bp));
	KASSERT(bp->bio_from != NULL,
	    ("NULL bio_from in g_slice_finish_hot(%p)", bp));
	gp = bp->bio_to->geom;
	gsp = gp->softc;
	cp = LIST_FIRST(&gp->consumer);
	KASSERT(cp != NULL, ("NULL consumer in g_slice_finish_hot(%p)", bp));
	idx = bp->bio_to->index;
	gsl = &gsp->slices[idx];

	bp2 = g_clone_bio(bp);
	if (bp2 == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}
	if (bp2->bio_offset + bp2->bio_length > gsl->length)
		bp2->bio_length = gsl->length - bp2->bio_offset;
	bp2->bio_done = g_std_done;
	bp2->bio_offset += gsl->offset;
	g_io_request(bp2, cp);
	return;
}