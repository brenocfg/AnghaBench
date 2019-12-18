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
struct gv_softc {int dummy; } ;
struct gv_plex {int /*<<< orphan*/  name; struct gv_softc* vinumconf; } ;
struct bio {int bio_cmd; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_pflags; struct gv_plex* bio_caller2; struct gv_plex* bio_caller1; void* bio_offset; int /*<<< orphan*/  bio_done; void* bio_length; } ;
typedef  void* off_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GV_BIO_MALLOC ; 
 int /*<<< orphan*/  GV_BIO_SYNCREQ ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * g_malloc (void*,int /*<<< orphan*/ ) ; 
 struct bio* g_new_bio () ; 
 int /*<<< orphan*/  gv_done ; 
 int /*<<< orphan*/  gv_post_bio (struct gv_softc*,struct bio*) ; 

int
gv_sync_request(struct gv_plex *from, struct gv_plex *to, off_t offset,
    off_t length, int type, caddr_t data)
{
	struct gv_softc *sc;
	struct bio *bp;

	KASSERT(from != NULL, ("NULL from"));
	KASSERT(to != NULL, ("NULL to"));
	sc = from->vinumconf;
	KASSERT(sc != NULL, ("NULL sc"));

	bp = g_new_bio();
	if (bp == NULL) {
		G_VINUM_DEBUG(0, "sync from '%s' failed at offset "
		    " %jd; out of memory", from->name, offset);
		return (ENOMEM);
	}
	bp->bio_length = length;
	bp->bio_done = gv_done;
	bp->bio_pflags |= GV_BIO_SYNCREQ;
	bp->bio_offset = offset;
	bp->bio_caller1 = from;		
	bp->bio_caller2 = to;
	bp->bio_cmd = type;
	if (data == NULL)
		data = g_malloc(length, M_WAITOK);
	bp->bio_pflags |= GV_BIO_MALLOC; /* Free on the next run. */
	bp->bio_data = data;

	/* Send down next. */
	gv_post_bio(sc, bp);
	//gv_plex_start(from, bp);
	return (0);
}