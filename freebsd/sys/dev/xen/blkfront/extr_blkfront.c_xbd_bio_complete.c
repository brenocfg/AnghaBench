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
struct xbd_softc {int dummy; } ;
struct xbd_command {scalar_t__ cm_status; struct bio* cm_bp; } ;
struct bio {int bio_flags; scalar_t__ bio_resid; int /*<<< orphan*/  bio_error; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 scalar_t__ BLKIF_RSP_OKAY ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  disk_err (struct bio*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  xbd_free_command (struct xbd_command*) ; 

__attribute__((used)) static void
xbd_bio_complete(struct xbd_softc *sc, struct xbd_command *cm)
{
	struct bio *bp;

	bp = cm->cm_bp;

	if (__predict_false(cm->cm_status != BLKIF_RSP_OKAY)) {
		disk_err(bp, "disk error" , -1, 0);
		printf(" status: %x\n", cm->cm_status);
		bp->bio_flags |= BIO_ERROR;
	}

	if (bp->bio_flags & BIO_ERROR)
		bp->bio_error = EIO;
	else
		bp->bio_resid = 0;

	xbd_free_command(cm);
	biodone(bp);
}