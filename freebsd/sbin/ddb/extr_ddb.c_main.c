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
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddb_main (int,char**) ; 
 int /*<<< orphan*/  ddb_readfile (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{

	/*
	 * If we've only got one argument and it's an absolute path to a file,
	 * interpret as a file to be read in.
	 */
	if (argc == 2 && argv[1][0] == '/' && access(argv[1], R_OK) == 0)
		ddb_readfile(argv[1]);
	else
		ddb_main(argc-1, argv+1);
	exit(EX_OK);
}