#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long dd_loc; int /*<<< orphan*/  dd_buf; int /*<<< orphan*/  dd_fd; int /*<<< orphan*/  dd_size; } ;
typedef  TYPE_1__ RST_DIR ;

/* Variables and functions */
 int DIRBLKSIZ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rounddown2 (long,int) ; 
 long rst_telldir (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
rst_seekdir(RST_DIR *dirp, long loc, long base)
{

	if (loc == rst_telldir(dirp))
		return;
	loc -= base;
	if (loc < 0)
		fprintf(stderr, "bad seek pointer to rst_seekdir %ld\n", loc);
	(void) lseek(dirp->dd_fd, base + rounddown2(loc, DIRBLKSIZ), SEEK_SET);
	dirp->dd_loc = loc & (DIRBLKSIZ - 1);
	if (dirp->dd_loc != 0)
		dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, DIRBLKSIZ);
}