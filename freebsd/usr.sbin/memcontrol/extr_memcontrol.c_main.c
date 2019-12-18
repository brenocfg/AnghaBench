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
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (int,int,char**) ;int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _PATH_MEM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* functions ; 
 int /*<<< orphan*/  help (int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int,char**) ; 

int
main(int argc, char *argv[])
{
    int		i, memfd;

    if (argc < 2) {
	help(NULL);
    } else {
	if ((memfd = open(_PATH_MEM, O_RDONLY)) == -1)
	    err(1, "can't open %s", _PATH_MEM);

	for (i = 0; functions[i].cmd != NULL; i++)
	    if (!strcmp(argv[1], functions[i].cmd))
		break;
	functions[i].func(memfd, argc - 1, argv + 1);
	close(memfd);
    }
    return(0);
}