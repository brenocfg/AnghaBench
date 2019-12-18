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
typedef  union ctl_io {int dummy; } ctl_io ;
struct TYPE_2__ {int flags; } ;
struct ctl_scsiio {TYPE_1__ io_hdr; int /*<<< orphan*/ * cdb; } ;
struct ctl_cmd_entry {int (* execute ) (struct ctl_scsiio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ABORT ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 struct ctl_cmd_entry* ctl_get_cmd_entry (struct ctl_scsiio*,int /*<<< orphan*/ *) ; 
 int stub1 (struct ctl_scsiio*) ; 

__attribute__((used)) static int
ctl_scsiio(struct ctl_scsiio *ctsio)
{
	int retval;
	const struct ctl_cmd_entry *entry;

	retval = CTL_RETVAL_COMPLETE;

	CTL_DEBUG_PRINT(("ctl_scsiio cdb[0]=%02X\n", ctsio->cdb[0]));

	entry = ctl_get_cmd_entry(ctsio, NULL);

	/*
	 * If this I/O has been aborted, just send it straight to
	 * ctl_done() without executing it.
	 */
	if (ctsio->io_hdr.flags & CTL_FLAG_ABORT) {
		ctl_done((union ctl_io *)ctsio);
		goto bailout;
	}

	/*
	 * All the checks should have been handled by ctl_scsiio_precheck().
	 * We should be clear now to just execute the I/O.
	 */
	retval = entry->execute(ctsio);

bailout:
	return (retval);
}