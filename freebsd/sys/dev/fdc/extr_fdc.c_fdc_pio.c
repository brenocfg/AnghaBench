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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct fdc_data {int /*<<< orphan*/ * ioff; int /*<<< orphan*/ * ioh; int /*<<< orphan*/  iot; TYPE_1__* fd; struct bio* bp; } ;
struct bio {scalar_t__ bio_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd_iosize; int /*<<< orphan*/ * fd_ioptr; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 size_t FD_YE_DATAPORT ; 
 int /*<<< orphan*/  bus_space_read_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdbcdr_wr (struct fdc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fdc_pio(struct fdc_data *fdc)
{
	u_char *cptr;
	struct bio *bp;
	u_int count;

	bp = fdc->bp;
	cptr = fdc->fd->fd_ioptr;
	count = fdc->fd->fd_iosize;

	if (bp->bio_cmd == BIO_READ) {
		fdbcdr_wr(fdc, 0, count);
		bus_space_read_multi_1(fdc->iot, fdc->ioh[FD_YE_DATAPORT],
		    fdc->ioff[FD_YE_DATAPORT], cptr, count);
	} else {
		bus_space_write_multi_1(fdc->iot, fdc->ioh[FD_YE_DATAPORT],
		    fdc->ioff[FD_YE_DATAPORT], cptr, count);
		fdbcdr_wr(fdc, 0, count);	/* needed? */
	}
}