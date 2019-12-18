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
typedef  scalar_t__ u_int ;
struct fdc_readid {int cyl; int head; } ;
struct fd_formb {int cyl; int head; } ;
struct fd_data {int sectorsize; TYPE_1__* ft; } ;
struct bio {int bio_pblkno; int bio_length; int bio_offset; int bio_flags; int bio_error; struct fd_data* bio_driver1; void* bio_data; scalar_t__ bio_cmd; } ;
struct TYPE_2__ {int heads; int sectrac; } ;

/* Variables and functions */
 int BIO_DONE ; 
 scalar_t__ BIO_FMT ; 
 scalar_t__ BIO_PROBE ; 
 scalar_t__ BIO_RDID ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  fd_enqueue (struct fd_data*,struct bio*) ; 
 int /*<<< orphan*/  free (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 struct bio* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tsleep (struct bio*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdmisccmd(struct fd_data *fd, u_int cmd, void *data)
{
	struct bio *bp;
	struct fd_formb *finfo;
	struct fdc_readid *idfield;
	int error;

	bp = malloc(sizeof(struct bio), M_TEMP, M_WAITOK | M_ZERO);

	/*
	 * Set up a bio request for fdstrategy().  bio_offset is faked
	 * so that fdstrategy() will seek to the requested
	 * cylinder, and use the desired head.
	 */
	bp->bio_cmd = cmd;
	if (cmd == BIO_FMT) {
		finfo = (struct fd_formb *)data;
		bp->bio_pblkno =
		    (finfo->cyl * fd->ft->heads + finfo->head) *
		    fd->ft->sectrac;
		bp->bio_length = sizeof *finfo;
	} else if (cmd == BIO_RDID) {
		idfield = (struct fdc_readid *)data;
		bp->bio_pblkno =
		    (idfield->cyl * fd->ft->heads + idfield->head) *
		    fd->ft->sectrac;
		bp->bio_length = sizeof(struct fdc_readid);
	} else if (cmd == BIO_PROBE) {
		/* nothing */
	} else
		panic("wrong cmd in fdmisccmd()");
	bp->bio_offset = bp->bio_pblkno * fd->sectorsize;
	bp->bio_data = data;
	bp->bio_driver1 = fd;
	bp->bio_flags = 0;

	fd_enqueue(fd, bp);

	do {
		tsleep(bp, PRIBIO, "fdwait", hz);
	} while (!(bp->bio_flags & BIO_DONE));
	error = bp->bio_error;

	free(bp, M_TEMP);
	return (error);
}