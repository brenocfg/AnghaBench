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

/* Variables and functions */
 int /*<<< orphan*/  MLXD_CHECKASYNC ; 
 int cmd_help (int,char**) ; 
 int /*<<< orphan*/  drivepath (int) ; 
 int driveunit (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
cmd_check(int argc, char *argv[])
{
    int		unit, fd, result;

    if (argc != 2)
	return(cmd_help(argc, argv));

    if ((unit = driveunit(argv[1])) == -1) {
	warnx("'%s' is not a valid drive", argv[1]);
    } else {
	
	/* Get the device */
	if ((fd = open(drivepath(unit), 0)) < 0) {
	    warn("can't open %s", drivepath(unit));
	} else {
	    /* Try to start the check */
	    if ((ioctl(fd, MLXD_CHECKASYNC, &result)) < 0) {
		switch(result) {
		case 0x0002:
		    warnx("one or more of the SCSI disks on which the drive '%s' depends is DEAD", argv[1]);
		    break;
		case 0x0105:
		    warnx("drive %s is invalid, or not a drive which can be checked", argv[1]);
		    break;
		case 0x0106:
		    warnx("drive rebuild or consistency check is already in progress on this controller");
		    break;
		default:
		    warn("ioctl MLXD_CHECKASYNC");
		}
	    }
	}
    }
    return(0);
}