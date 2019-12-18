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
struct gv_sd {scalar_t__ drive_offset; } ;
struct gv_raid5_packet {int /*<<< orphan*/  length; scalar_t__ lockbase; } ;
struct bio {struct gv_raid5_packet* bio_caller2; struct gv_sd* bio_caller1; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_length; scalar_t__ bio_offset; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_cflags; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GV_BIO_MALLOC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/ * g_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gv_done ; 

__attribute__((used)) static struct bio *
gv_raid5_clone_bio(struct bio *bp, struct gv_sd *s, struct gv_raid5_packet *wp,
    caddr_t addr, int use_wp)
{
	struct bio *cbp;

	cbp = g_clone_bio(bp);
	if (cbp == NULL)
		return (NULL);
	if (addr == NULL) {
		cbp->bio_data = g_malloc(wp->length, M_WAITOK | M_ZERO);
		cbp->bio_cflags |= GV_BIO_MALLOC;
	} else
		cbp->bio_data = addr;
	cbp->bio_offset = wp->lockbase + s->drive_offset;
	cbp->bio_length = wp->length;
	cbp->bio_done = gv_done;
	cbp->bio_caller1 = s;
	if (use_wp)
		cbp->bio_caller2 = wp;

	return (cbp);
}