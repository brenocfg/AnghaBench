#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kern_data_resid; int /*<<< orphan*/  kern_data_ptr; } ;
struct TYPE_5__ {scalar_t__ io_type; scalar_t__ port_status; int status; int flags; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;

/* Variables and functions */
 int CTL_DEBUG_CDB_DATA ; 
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_ALLOCATED ; 
 int CTL_FLAG_DATA_IN ; 
 int CTL_FLAG_DATA_MASK ; 
 int CTL_FLAG_DATA_OUT ; 
 scalar_t__ CTL_IO_SCSI ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  ctl_data_print (union ctl_io*) ; 
 int ctl_debug ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int ctl_scsiio (TYPE_2__*) ; 
 int /*<<< orphan*/  ctl_set_internal_failure (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ctl_set_invalid_field_ciu (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctl_config_move_done(union ctl_io *io)
{
	int retval;

	CTL_DEBUG_PRINT(("ctl_config_move_done\n"));
	KASSERT(io->io_hdr.io_type == CTL_IO_SCSI,
	    ("Config I/O type isn't CTL_IO_SCSI (%d)!", io->io_hdr.io_type));

	if ((io->io_hdr.port_status != 0) &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE ||
	     (io->io_hdr.status & CTL_STATUS_MASK) == CTL_SUCCESS)) {
		ctl_set_internal_failure(&io->scsiio, /*sks_valid*/ 1,
		    /*retry_count*/ io->io_hdr.port_status);
	} else if (io->scsiio.kern_data_resid != 0 &&
	    (io->io_hdr.flags & CTL_FLAG_DATA_MASK) == CTL_FLAG_DATA_OUT &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE ||
	     (io->io_hdr.status & CTL_STATUS_MASK) == CTL_SUCCESS)) {
		ctl_set_invalid_field_ciu(&io->scsiio);
	}

	if (ctl_debug & CTL_DEBUG_CDB_DATA)
		ctl_data_print(io);
	if (((io->io_hdr.flags & CTL_FLAG_DATA_MASK) == CTL_FLAG_DATA_IN) ||
	    ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	     (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS) ||
	    ((io->io_hdr.flags & CTL_FLAG_ABORT) != 0)) {
		/*
		 * XXX KDM just assuming a single pointer here, and not a
		 * S/G list.  If we start using S/G lists for config data,
		 * we'll need to know how to clean them up here as well.
		 */
		if (io->io_hdr.flags & CTL_FLAG_ALLOCATED)
			free(io->scsiio.kern_data_ptr, M_CTL);
		ctl_done(io);
		retval = CTL_RETVAL_COMPLETE;
	} else {
		/*
		 * XXX KDM now we need to continue data movement.  Some
		 * options:
		 * - call ctl_scsiio() again?  We don't do this for data
		 *   writes, because for those at least we know ahead of
		 *   time where the write will go and how long it is.  For
		 *   config writes, though, that information is largely
		 *   contained within the write itself, thus we need to
		 *   parse out the data again.
		 *
		 * - Call some other function once the data is in?
		 */

		/*
		 * XXX KDM call ctl_scsiio() again for now, and check flag
		 * bits to see whether we're allocated or not.
		 */
		retval = ctl_scsiio(&io->scsiio);
	}
	return (retval);
}