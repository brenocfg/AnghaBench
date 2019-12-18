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
struct bio {int bio_cmd; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_pflags; void* bio_length; void* bio_offset; struct gv_plex* bio_caller1; scalar_t__ bio_error; int /*<<< orphan*/  bio_done; } ;
typedef  void* off_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GV_BIO_GROW ; 
 int /*<<< orphan*/  GV_BIO_MALLOC ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * g_malloc (void*,int /*<<< orphan*/ ) ; 
 struct bio* g_new_bio () ; 
 int /*<<< orphan*/  gv_done ; 
 int /*<<< orphan*/  gv_post_bio (struct gv_softc*,struct bio*) ; 

int
gv_grow_request(struct gv_plex *p, off_t offset, off_t length, int type,
    caddr_t data)
{
	struct gv_softc *sc;
	struct bio *bp;

	KASSERT(p != NULL, ("gv_grow_request: NULL p"));
	sc = p->vinumconf;
	KASSERT(sc != NULL, ("gv_grow_request: NULL sc"));

	bp = g_new_bio();
	if (bp == NULL) {
		G_VINUM_DEBUG(0, "grow of %s failed creating bio: "
		    "out of memory", p->name);
		return (ENOMEM);
	}

	bp->bio_cmd = type;
	bp->bio_done = gv_done;
	bp->bio_error = 0;
	bp->bio_caller1 = p;
	bp->bio_offset = offset;
	bp->bio_length = length;
	bp->bio_pflags |= GV_BIO_GROW;
	if (data == NULL)
		data = g_malloc(length, M_WAITOK);
	bp->bio_pflags |= GV_BIO_MALLOC;
	bp->bio_data = data;

	gv_post_bio(sc, bp);
	//gv_plex_start(p, bp);
	return (0);
}