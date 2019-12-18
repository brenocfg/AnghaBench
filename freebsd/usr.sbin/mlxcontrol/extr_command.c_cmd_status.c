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
 int cmd_help (int,char**) ; 
 int /*<<< orphan*/  controller_print ; 
 int driveunit (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mlx_foreach (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlxd_foreach (int /*<<< orphan*/  (*) (int,int*),int*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  status_print (int,int*) ; 
 int status_result ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
cmd_status(int argc, char *argv[])
{
    int		ch, verbosity = 1, i, unit;

    optreset = 1;
    optind = 1;
    while ((ch = getopt(argc, argv, "qv")) != -1)
	switch(ch) {
	case 'q':
	    verbosity = 0;
	    break;
	case 'v':
	    verbosity = 2;
	    break;
	default:
	    return(cmd_help(argc, argv));
	}
    argc -= optind;
    argv += optind;

    if (argc < 1) {
	mlx_foreach(controller_print, &verbosity);
	mlxd_foreach(status_print, &verbosity);
    } else {
	for (i = 0; i < argc; i++) {
	    if ((unit = driveunit(argv[i])) == -1) {
		warnx("'%s' is not a valid drive", argv[i]);
	    } else {
		status_print(unit, &verbosity);
	    }
	}
    }
    return(status_result);
}