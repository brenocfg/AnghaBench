#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_provider {int flags; int acr; int acw; int ace; int sectorsize; int stripesize; int mediasize; TYPE_1__* geom; } ;
struct fdc_data {int /*<<< orphan*/  fdc_mtx; } ;
struct fd_data {int options; int flags; int sectorsize; TYPE_2__* ft; int /*<<< orphan*/  dev; struct fdc_data* fdc; } ;
struct TYPE_4__ {int heads; int sectrac; int tracks; } ;
struct TYPE_3__ {struct fd_data* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_PROBE ; 
 int ENXIO ; 
 int EROFS ; 
 int FDOPT_NOERRLOG ; 
 int FDOPT_NOERROR ; 
 int FDOPT_NORETRY ; 
 int FD_EMPTY ; 
 int FD_NEWDISK ; 
 int FD_NO_CHLINE ; 
 int FD_WP ; 
 int G_PF_WITHER ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 scalar_t__ fdautoselect (struct fd_data*) ; 
 scalar_t__ fdmisccmd (struct fd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fd_access(struct g_provider *pp, int r, int w, int e)
{
	struct fd_data *fd;
	struct fdc_data *fdc;
	int ar, aw, ae;
	int busy;

	fd = pp->geom->softc;
	fdc = fd->fdc;

	/*
	 * If our provider is withering, we can only get negative requests
	 * and we don't want to even see them
	 */
	if (pp->flags & G_PF_WITHER)
		return (0);

	ar = r + pp->acr;
	aw = w + pp->acw;
	ae = e + pp->ace;

	if (ar == 0 && aw == 0 && ae == 0) {
		fd->options &= ~(FDOPT_NORETRY | FDOPT_NOERRLOG | FDOPT_NOERROR);
		device_unbusy(fd->dev);
		return (0);
	}

	busy = 0;
	if (pp->acr == 0 && pp->acw == 0 && pp->ace == 0) {
		if (fdmisccmd(fd, BIO_PROBE, NULL))
			return (ENXIO);
		if (fd->flags & FD_EMPTY)
			return (ENXIO);
		if (fd->flags & FD_NEWDISK) {
			if (fdautoselect(fd) != 0 &&
			    (device_get_flags(fd->dev) & FD_NO_CHLINE)) {
				mtx_lock(&fdc->fdc_mtx);
				fd->flags |= FD_EMPTY;
				mtx_unlock(&fdc->fdc_mtx);
				return (ENXIO);
			}
			mtx_lock(&fdc->fdc_mtx);
			fd->flags &= ~FD_NEWDISK;
			mtx_unlock(&fdc->fdc_mtx);
		}
		device_busy(fd->dev);
		busy = 1;
	}

	if (w > 0 && (fd->flags & FD_WP)) {
		if (busy)
			device_unbusy(fd->dev);
		return (EROFS);
	}

	pp->sectorsize = fd->sectorsize;
	pp->stripesize = fd->ft->heads * fd->ft->sectrac * fd->sectorsize;
	pp->mediasize = pp->stripesize * fd->ft->tracks;
	return (0);
}