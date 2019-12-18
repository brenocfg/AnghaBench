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
struct mlx_rebuild_request {int rr_status; int /*<<< orphan*/  rr_target; int /*<<< orphan*/  rr_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_REBUILDASYNC ; 
 int cmd_help (int,char**) ; 
 int /*<<< orphan*/  ctrlrpath (int) ; 
 int ctrlrunit (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mlx_rebuild_request*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
cmd_rebuild(int argc, char *argv[])
{
    struct mlx_rebuild_request	rb;
    int				unit, fd;

    if (argc != 3)
	return(cmd_help(argc, argv));

    /* parse arguments */
    if ((unit = ctrlrunit(argv[1])) == -1) {
	warnx("'%s' is not a valid controller", argv[1]);
	return(1);
    }
    /* try diskXXXX and unknownXXXX as we report the latter for a dead drive ... */
    if ((sscanf(argv[2], "disk%2d%2d", &rb.rr_channel, &rb.rr_target) != 2) &&
	(sscanf(argv[2], "unknown%2d%2d", &rb.rr_channel, &rb.rr_target) != 2)) {	
	warnx("'%s' is not a valid physical drive", argv[2]);
	return(1);
    }
    /* get the device */
    if ((fd = open(ctrlrpath(unit), 0)) < 0) {
	warn("can't open %s", ctrlrpath(unit));
	return(1);
    }
    /* try to start the rebuild */
    if ((ioctl(fd, MLX_REBUILDASYNC, &rb)) < 0) {
	switch(rb.rr_status) {
	case 0x0002:
	    warnx("the drive at %d:%d is already ONLINE", rb.rr_channel, rb.rr_target);
	    break;
	case 0x0004:
	    warnx("drive failed during rebuild");
	    break;
	case 0x0105:
	    warnx("there is no drive at channel %d, target %d", rb.rr_channel, rb.rr_target);
	    break;
	case 0x0106:
	    warnx("drive rebuild or consistency check is already in progress on this controller");
	    break;
	default:
	    warn("ioctl MLXD_REBUILDASYNC");
	}
    }
    return(0);
}