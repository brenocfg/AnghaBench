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
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fill_blocks () ; 
 int /*<<< orphan*/  fill_inodes () ; 

int
main(int argc, char *argv[])
{

	if (argc != 2)
		err(-1, "usage: ufs_uprintf /non_optional_path");

	if (chdir(argv[1]) < 0)
		err(-1, "chdir(%s)", argv[1]);

	fill_blocks();

	fill_inodes();

	return (0);
}