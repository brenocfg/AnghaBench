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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rename (char*,char*) ; 

int
rename_main(int argc, char **argv)
{

	if (argc < 3)
		return EXIT_FAILURE;

	if (rename(argv[1], argv[2]) == -1) {
		perror("rename");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}