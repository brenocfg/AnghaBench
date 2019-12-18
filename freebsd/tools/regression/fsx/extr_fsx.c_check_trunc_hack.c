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
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  prt (char*) ; 

void
check_trunc_hack(void)
{
	struct stat statbuf;

	ftruncate(fd, (off_t)0);
	ftruncate(fd, (off_t)100000);
	fstat(fd, &statbuf);
	if (statbuf.st_size != (off_t)100000) {
		prt("no extend on truncate! not posix!\n");
		exit(130);
	}
	ftruncate(fd, (off_t)0);
}