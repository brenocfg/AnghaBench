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
 int EEXIST ; 
 int FTW_MOUNT ; 
 int FTW_PHYS ; 
 int /*<<< orphan*/  compare_function ; 
 int /*<<< orphan*/  exit (int) ; 
 int nftw (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
find_inum(char *path)
{
	int ret;

	ret = nftw(path, compare_function, 1, FTW_PHYS|FTW_MOUNT);
	if (ret != EEXIST && ret != 0) {
		perror("ftw");
		exit(ret);
	}
}