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
typedef  int u_int ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdsect(int fd, off_t blockno, u_int sectorsize)
{
	int error;

	if (lseek(fd, (off_t)blockno * sectorsize, SEEK_SET) == -1)
		err(1, "lseek");
	error = read(fd, buf, sectorsize);
	if (error == -1)
		err(1, "read");
	if (error != (int)sectorsize)
		errx(1, "disk too small for test.");
}