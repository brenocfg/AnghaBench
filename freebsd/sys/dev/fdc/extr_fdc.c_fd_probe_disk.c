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
struct fdc_data {int /*<<< orphan*/  fdc_mtx; } ;
struct fd_data {int options; int fdsu; int /*<<< orphan*/  flags; struct fdc_data* fdc; } ;

/* Variables and functions */
 int FDI_DCHG ; 
 int FDOPT_NOERRLOG ; 
 int FDOPT_NORETRY ; 
 int /*<<< orphan*/  FD_EMPTY ; 
 int /*<<< orphan*/  FD_NEWDISK ; 
 scalar_t__ FD_NOT_VALID ; 
 int /*<<< orphan*/  FD_WP ; 
 int /*<<< orphan*/  NE7CMD_RECAL ; 
 int /*<<< orphan*/  NE7CMD_SEEK ; 
 int NE7_ST3_WP ; 
 int /*<<< orphan*/  PRIBIO ; 
 int debugflags ; 
 scalar_t__ fdc_cmd (struct fdc_data*,int,int /*<<< orphan*/ ,int,int,...) ; 
 scalar_t__ fdc_sense_drive (struct fdc_data*,int*) ; 
 scalar_t__ fdc_sense_int (struct fdc_data*,int*,int*) ; 
 int fdin_rd (struct fdc_data*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tsleep (struct fdc_data*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fd_probe_disk(struct fd_data *fd, int *recal)
{
	struct fdc_data *fdc;
	int st0, st3, cyl;
	int oopts, ret;

	fdc = fd->fdc;
	oopts = fd->options;
	fd->options |= FDOPT_NOERRLOG | FDOPT_NORETRY;
	ret = 1;

	/*
	 * First recal, then seek to cyl#1, this clears the old condition on
	 * the disk change line so we can examine it for current status.
	 */
	if (debugflags & 0x40)
		printf("New disk in probe\n");
	mtx_lock(&fdc->fdc_mtx);
	fd->flags |= FD_NEWDISK;
	mtx_unlock(&fdc->fdc_mtx);
	if (fdc_cmd(fdc, 2, NE7CMD_RECAL, fd->fdsu, 0))
		goto done;
	tsleep(fdc, PRIBIO, "fdrecal", hz);
	if (fdc_sense_int(fdc, &st0, &cyl) == FD_NOT_VALID)
		goto done;	/* XXX */
	if ((st0 & 0xc0) || cyl != 0)
		goto done;

	/* Seek to track 1 */
	if (fdc_cmd(fdc, 3, NE7CMD_SEEK, fd->fdsu, 1, 0))
		goto done;
	tsleep(fdc, PRIBIO, "fdseek", hz);
	if (fdc_sense_int(fdc, &st0, &cyl) == FD_NOT_VALID)
		goto done;	/* XXX */
	*recal |= (1 << fd->fdsu);
	if (fdin_rd(fdc) & FDI_DCHG) {
		if (debugflags & 0x40)
			printf("Empty in probe\n");
		mtx_lock(&fdc->fdc_mtx);
		fd->flags |= FD_EMPTY;
		mtx_unlock(&fdc->fdc_mtx);
	} else {
		if (fdc_sense_drive(fdc, &st3) != 0)
			goto done;
		if (debugflags & 0x40)
			printf("Got disk in probe\n");
		mtx_lock(&fdc->fdc_mtx);
		fd->flags &= ~FD_EMPTY;
		if (st3 & NE7_ST3_WP)
			fd->flags |= FD_WP;
		else
			fd->flags &= ~FD_WP;
		mtx_unlock(&fdc->fdc_mtx);
	}
	ret = 0;

done:
	fd->options = oopts;
	return (ret);
}