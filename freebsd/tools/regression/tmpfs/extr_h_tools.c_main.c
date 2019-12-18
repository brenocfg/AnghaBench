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
 int EXIT_FAILURE ; 
 int getfh_main (int,char**) ; 
 int kqueue_main (int,char**) ; 
 int rename_main (int,char**) ; 
 int sockets_main (int,char**) ; 
 int statvfs_main (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char **argv)
{
	int error;

	if (argc < 2)
		return EXIT_FAILURE;

	argc -= 1;
	argv += 1;

	if (strcmp(argv[0], "getfh") == 0)
		error = getfh_main(argc, argv);
	else if (strcmp(argv[0], "kqueue") == 0)
		error = kqueue_main(argc, argv);
	else if (strcmp(argv[0], "rename") == 0)
		error = rename_main(argc, argv);
	else if (strcmp(argv[0], "sockets") == 0)
		error = sockets_main(argc, argv);
	else if (strcmp(argv[0], "statvfs") == 0)
		error = statvfs_main(argc, argv);
	else
		error = EXIT_FAILURE;

	return error;
}