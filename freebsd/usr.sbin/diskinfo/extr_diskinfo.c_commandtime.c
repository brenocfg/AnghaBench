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
typedef  int /*<<< orphan*/  u_int ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  T0 () ; 
 double delta_t () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rdmega (int) ; 
 int /*<<< orphan*/  rdsect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
commandtime(int fd, off_t mediasize, u_int sectorsize)
{	
	double dtmega, dtsector;
	int i;

	printf("I/O command overhead:\n");
	i = mediasize;
	rdsect(fd, 0, sectorsize);
	T0();
	for (i = 0; i < 10; i++)
		rdmega(fd);
	dtmega = delta_t();

	printf("\ttime to read 10MB block    %10.6f sec\t= %8.3f msec/sector\n",
		dtmega, dtmega*100/2048);

	rdsect(fd, 0, sectorsize);
	T0();
	for (i = 0; i < 20480; i++)
		rdsect(fd, 0, sectorsize);
	dtsector = delta_t();

	printf("\ttime to read 20480 sectors %10.6f sec\t= %8.3f msec/sector\n",
		dtsector, dtsector*100/2048);
	printf("\tcalculated command overhead\t\t\t= %8.3f msec/sector\n",
		(dtsector - dtmega)*100/2048);

	printf("\n");
	return;
}