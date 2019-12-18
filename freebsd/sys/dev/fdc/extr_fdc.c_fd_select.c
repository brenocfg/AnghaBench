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
struct fdc_data {int fdout; } ;
struct fd_data {int fdsu; struct fdc_data* fdc; } ;

/* Variables and functions */
 int FDO_FDMAEN ; 
 int FDO_FDSEL ; 
 int FDO_FRST ; 
 int /*<<< orphan*/  fdout_wr (struct fdc_data*,int) ; 

__attribute__((used)) static void
fd_select(struct fd_data *fd)
{
	struct fdc_data *fdc;

	/* XXX: lock controller */
	fdc = fd->fdc;
	fdc->fdout &= ~FDO_FDSEL;
	fdc->fdout |= FDO_FDMAEN | FDO_FRST | fd->fdsu;
	fdout_wr(fdc, fdc->fdout);
}