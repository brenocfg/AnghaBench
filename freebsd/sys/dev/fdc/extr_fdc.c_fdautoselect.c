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
struct fdc_readid {int cyl; int head; scalar_t__ secshift; } ;
struct fd_type {int heads; scalar_t__ secsize; } ;
struct fd_data {size_t type; int options; TYPE_1__* ft; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int flags; scalar_t__ heads; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_RDID ; 
 int FDOPT_NOERRLOG ; 
 int FDOPT_NORETRY ; 
 int FL_AUTO ; 
 int debugflags ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct fd_type** fd_native_types ; 
 int fdmisccmd (struct fd_data*,int /*<<< orphan*/ ,struct fdc_readid*) ; 
 int /*<<< orphan*/  fdprinttype (TYPE_1__*) ; 
 int /*<<< orphan*/  fdsettype (struct fd_data*,struct fd_type*) ; 

__attribute__((used)) static int
fdautoselect(struct fd_data *fd)
{
	struct fd_type *fdtp;
	struct fdc_readid id;
	int oopts, rv;

	if (!(fd->ft->flags & FL_AUTO))
		return (0);

	fdtp = fd_native_types[fd->type];
	fdsettype(fd, fdtp);
	if (!(fd->ft->flags & FL_AUTO))
		return (0);

	/*
	 * Try reading sector ID fields, first at cylinder 0, head 0,
	 * then at cylinder 2, head N.  We don't probe cylinder 1,
	 * since for 5.25in DD media in a HD drive, there are no data
	 * to read (2 step pulses per media cylinder required).  For
	 * two-sided media, the second probe always goes to head 1, so
	 * we can tell them apart from single-sided media.  As a
	 * side-effect this means that single-sided media should be
	 * mentioned in the search list after two-sided media of an
	 * otherwise identical density.  Media with a different number
	 * of sectors per track but otherwise identical parameters
	 * cannot be distinguished at all.
	 *
	 * If we successfully read an ID field on both cylinders where
	 * the recorded values match our expectation, we are done.
	 * Otherwise, we try the next density entry from the table.
	 *
	 * Stepping to cylinder 2 has the side-effect of clearing the
	 * unit attention bit.
	 */
	oopts = fd->options;
	fd->options |= FDOPT_NOERRLOG | FDOPT_NORETRY;
	for (; fdtp->heads; fdtp++) {
		fdsettype(fd, fdtp);

		id.cyl = id.head = 0;
		rv = fdmisccmd(fd, BIO_RDID, &id);
		if (rv != 0)
			continue;
		if (id.cyl != 0 || id.head != 0 || id.secshift != fdtp->secsize)
			continue;
		id.cyl = 2;
		id.head = fd->ft->heads - 1;
		rv = fdmisccmd(fd, BIO_RDID, &id);
		if (id.cyl != 2 || id.head != fdtp->heads - 1 ||
		    id.secshift != fdtp->secsize)
			continue;
		if (rv == 0)
			break;
	}

	fd->options = oopts;
	if (fdtp->heads == 0) {
		if (debugflags & 0x40)
			device_printf(fd->dev, "autoselection failed\n");
		fdsettype(fd, fd_native_types[fd->type]);
		return (-1);
	} else {
		if (debugflags & 0x40) {
			device_printf(fd->dev,
			    "autoselected %d KB medium\n",
			    fd->ft->size / 2);
			fdprinttype(fd->ft);
		}
		return (0);
	}
}