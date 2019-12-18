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
typedef  int uint64_t ;

/* Variables and functions */
#define  EACCES 130 
#define  ENODEV 129 
#define  EROFS 128 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 

__attribute__((used)) static bool
vfs_should_downgrade_to_ro_mount(uint64_t fsflags, int error)
{
	/* This is an upgrade of an exisiting mount. */
	if ((fsflags & MNT_UPDATE) != 0)
		return (false);
	/* This is already an R/O mount. */
	if ((fsflags & MNT_RDONLY) != 0)
		return (false);

	switch (error) {
	case ENODEV:	/* generic, geom, ... */
	case EACCES:	/* cam/scsi, ... */
	case EROFS:	/* md, mmcsd, ... */
		/*
		 * These errors can be returned by the storage layer to signal
		 * that the media is read-only.  No harm in the R/O mount
		 * attempt if the error was returned for some other reason.
		 */
		return (true);
	default:
		return (false);
	}
}