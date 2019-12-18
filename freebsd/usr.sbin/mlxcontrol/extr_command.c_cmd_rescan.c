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
 int ctrlrunit (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mlx_foreach (int /*<<< orphan*/  (*) (int,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  rescan_ctrlr (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
cmd_rescan(int argc, char *argv[]) 
{
    int		all = 0, i, ch, unit;

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
	mlx_foreach(rescan_ctrlr, NULL);
    } else {
	for (i = 0; i < argc; i++) {
	    if ((unit = ctrlrunit(argv[i])) == -1) {
		warnx("'%s' is not a valid controller", argv[i]);
	    } else {
		rescan_ctrlr(unit, NULL);
	    }
	}
    }
    return(0);
}