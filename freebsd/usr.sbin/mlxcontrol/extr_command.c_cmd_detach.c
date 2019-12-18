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
struct mlxd_foreach_action {int* arg; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int cmd_help (int,char**) ; 
 int ctrlrunit (char*) ; 
 int /*<<< orphan*/  detach_drive ; 
 int driveunit (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mlx_foreach (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlxd_foreach_ctrlr (int,struct mlxd_foreach_action*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
cmd_detach(int argc, char *argv[]) 
{
    struct mlxd_foreach_action	ma;
    int				all = 0, i, ch, unit;

    optreset = 1;
    optind = 1;
    while ((ch = getopt(argc, argv, "a")) != -1)
	switch(ch) {
	case 'a':
	    all = 1;
	    break;
	default:
	    return(cmd_help(argc, argv));
	}
    argc -= optind;
    argv += optind;

    if (all) {
	ma.func = detach_drive;
	ma.arg = &unit;
	for (i = 0; i < argc; i++) {
	    if ((unit = ctrlrunit(argv[i])) == -1) {
		warnx("'%s' is not a valid controller", argv[i]);
	    } else {
		mlxd_foreach_ctrlr(unit, &ma);
	    }
	}
    } else {
	for (i = 0; i < argc; i++) {
	    if ((unit = driveunit(argv[i])) == -1) {
		warnx("'%s' is not a valid drive", argv[i]);
	    } else {
		/* run across all controllers to find this drive */
		mlx_foreach(detach_drive, &unit);
	    }
	}
    }
    return(0);
}