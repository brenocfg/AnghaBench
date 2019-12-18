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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  iops (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
iopsbench(int fd, off_t mediasize, u_int sectorsize)
{
	printf("Asynchronous random reads:\n");

	printf("\tsectorsize:  ");
	iops(fd, mediasize, sectorsize);

	if (sectorsize != 4096) {
		printf("\t4 kbytes:    ");
		iops(fd, mediasize, 4096);
	}

	printf("\t32 kbytes:   ");
	iops(fd, mediasize, 32 * 1024);

	printf("\t128 kbytes:  ");
	iops(fd, mediasize, 128 * 1024);

	printf("\n");
}