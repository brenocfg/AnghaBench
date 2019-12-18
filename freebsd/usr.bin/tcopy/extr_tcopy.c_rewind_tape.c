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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTREW ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeop (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rewind_tape(int fd)
{
	struct stat sp;

	if(fstat(fd, &sp))
		errx(12, "fstat in rewind");

	/*
	 * don't want to do tape ioctl on regular files:
	 */
	if( S_ISREG(sp.st_mode) ) {
		if( lseek(fd, 0, SEEK_SET) == -1 )
			errx(13, "lseek");
	} else
		/*  assume its a tape	*/
		writeop(fd, MTREW);
}