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
 int SHAPEONLY ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int flags ; 
 int /*<<< orphan*/  getargs (int,char**) ; 
 int /*<<< orphan*/  getfile () ; 
 int icols ; 
 int irows ; 
 int /*<<< orphan*/  prepfile () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  putfile () ; 

int
main(int argc, char *argv[])
{
	getargs(argc, argv);
	getfile();
	if (flags & SHAPEONLY) {
		printf("%d %d\n", irows, icols);
		exit(0);
	}
	prepfile();
	putfile();
	exit(0);
}