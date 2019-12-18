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
typedef  size_t u_int ;
struct g_slicer {size_t nhotspot; int (* start ) (struct bio*) ;struct g_slice* slices; int /*<<< orphan*/  hot; struct g_slice_hot* hotspot; } ;
struct g_slice_hot {int ract; int wact; int dact; scalar_t__ offset; scalar_t__ length; } ;
struct g_slice {scalar_t__ length; scalar_t__ offset; } ;
struct g_provider {int index; struct g_geom* geom; } ;
struct g_kerneldump {scalar_t__ length; scalar_t__ offset; } ;
struct g_geom {int /*<<< orphan*/  consumer; struct g_slicer* softc; } ;
struct g_consumer {int dummy; } ;
struct bio {int bio_cmd; void* bio_done; scalar_t__ bio_data; int /*<<< orphan*/  bio_attribute; scalar_t__ bio_offset; scalar_t__ bio_length; struct g_provider* bio_to; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
#define  BIO_DELETE 136 
#define  BIO_FLUSH 135 
#define  BIO_GETATTR 134 
#define  BIO_READ 133 
#define  BIO_WRITE 132 
 int EINVAL ; 
 int EJUSTRETURN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
#define  G_SLICE_HOT_ALLOW 131 
#define  G_SLICE_HOT_CALL 130 
#define  G_SLICE_HOT_DENY 129 
#define  G_SLICE_HOT_START 128 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int g_post_event (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,struct g_geom*,int /*<<< orphan*/ *) ; 
 void* g_slice_done ; 
 void* g_std_done ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct bio*) ; 
 int stub2 (struct bio*) ; 

__attribute__((used)) static void
g_slice_start(struct bio *bp)
{
	struct bio *bp2;
	struct g_provider *pp;
	struct g_geom *gp;
	struct g_consumer *cp;
	struct g_slicer *gsp;
	struct g_slice *gsl;
	struct g_slice_hot *ghp;
	int idx, error;
	u_int m_index;
	off_t t;

	pp = bp->bio_to;
	gp = pp->geom;
	gsp = gp->softc;
	cp = LIST_FIRST(&gp->consumer);
	idx = pp->index;
	gsl = &gsp->slices[idx];
	switch(bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
		if (bp->bio_offset > gsl->length) {
			g_io_deliver(bp, EINVAL); /* XXX: EWHAT ? */
			return;
		}
		/*
		 * Check if we collide with any hot spaces, and call the
		 * method once if so.
		 */
		t = bp->bio_offset + gsl->offset;
		for (m_index = 0; m_index < gsp->nhotspot; m_index++) {
			ghp = &gsp->hotspot[m_index];
			if (t >= ghp->offset + ghp->length)
				continue;
			if (t + bp->bio_length <= ghp->offset)
				continue;
			switch(bp->bio_cmd) {
			case BIO_READ:		idx = ghp->ract; break;
			case BIO_WRITE:		idx = ghp->wact; break;
			case BIO_DELETE:	idx = ghp->dact; break;
			}
			switch(idx) {
			case G_SLICE_HOT_ALLOW:
				/* Fall out and continue normal processing */
				continue;
			case G_SLICE_HOT_DENY:
				g_io_deliver(bp, EROFS);
				return;
			case G_SLICE_HOT_START:
				error = gsp->start(bp);
				if (error && error != EJUSTRETURN)
					g_io_deliver(bp, error);
				return;
			case G_SLICE_HOT_CALL:
				error = g_post_event(gsp->hot, bp, M_NOWAIT,
				    gp, NULL);
				if (error)
					g_io_deliver(bp, error);
				return;
			}
			break;
		}
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
	case BIO_GETATTR:
		/* Give the real method a chance to override */
		if (gsp->start != NULL && gsp->start(bp))
			return;
		if (!strcmp("GEOM::ident", bp->bio_attribute)) {
			bp2 = g_clone_bio(bp);
			if (bp2 == NULL) {
				g_io_deliver(bp, ENOMEM);
				return;
			}
			bp2->bio_done = g_slice_done;
			g_io_request(bp2, cp);
			return;
		}
		if (!strcmp("GEOM::kerneldump", bp->bio_attribute)) {
			struct g_kerneldump *gkd;

			gkd = (struct g_kerneldump *)bp->bio_data;
			gkd->offset += gsp->slices[idx].offset;
			if (gkd->length > gsp->slices[idx].length)
				gkd->length = gsp->slices[idx].length;
			/* now, pass it on downwards... */
		}
		/* FALLTHROUGH */
	case BIO_FLUSH:
		bp2 = g_clone_bio(bp);
		if (bp2 == NULL) {
			g_io_deliver(bp, ENOMEM);
			return;
		}
		bp2->bio_done = g_std_done;
		g_io_request(bp2, cp);
		break;
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		return;
	}
}