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
 int /*<<< orphan*/  T0 () ; 
 int /*<<< orphan*/  TN (int) ; 
 int /*<<< orphan*/  TR (int) ; 
 int flsll (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rdmega (int) ; 
 int /*<<< orphan*/  rdsect (int,int,int) ; 

__attribute__((used)) static void
speeddisk(int fd, off_t mediasize, u_int sectorsize)
{
	int bulk, i;
	off_t b0, b1, sectorcount, step;

	/*
	 * Drives smaller than 1MB produce negative sector numbers,
	 * as do 2048 or fewer sectors.
	 */
	sectorcount = mediasize / sectorsize;
	if (mediasize < 1024 * 1024 || sectorcount < 2048)
		return;


	step = 1ULL << (flsll(sectorcount / (4 * 200)) - 1);
	if (step > 16384)
		step = 16384;
	bulk = mediasize / (1024 * 1024);
	if (bulk > 100)
		bulk = 100;

	printf("Seek times:\n");
	printf("\tFull stroke:\t");
	b0 = 0;
	b1 = sectorcount - step;
	T0();
	for (i = 0; i < 125; i++) {
		rdsect(fd, b0, sectorsize);
		b0 += step;
		rdsect(fd, b1, sectorsize);
		b1 -= step;
	}
	TN(250);

	printf("\tHalf stroke:\t");
	b0 = sectorcount / 4;
	b1 = b0 + sectorcount / 2;
	T0();
	for (i = 0; i < 125; i++) {
		rdsect(fd, b0, sectorsize);
		b0 += step;
		rdsect(fd, b1, sectorsize);
		b1 += step;
	}
	TN(250);
	printf("\tQuarter stroke:\t");
	b0 = sectorcount / 4;
	b1 = b0 + sectorcount / 4;
	T0();
	for (i = 0; i < 250; i++) {
		rdsect(fd, b0, sectorsize);
		b0 += step;
		rdsect(fd, b1, sectorsize);
		b1 += step;
	}
	TN(500);

	printf("\tShort forward:\t");
	b0 = sectorcount / 2;
	T0();
	for (i = 0; i < 400; i++) {
		rdsect(fd, b0, sectorsize);
		b0 += step;
	}
	TN(400);

	printf("\tShort backward:\t");
	b0 = sectorcount / 2;
	T0();
	for (i = 0; i < 400; i++) {
		rdsect(fd, b0, sectorsize);
		b0 -= step;
	}
	TN(400);

	printf("\tSeq outer:\t");
	b0 = 0;
	T0();
	for (i = 0; i < 2048; i++) {
		rdsect(fd, b0, sectorsize);
		b0++;
	}
	TN(2048);

	printf("\tSeq inner:\t");
	b0 = sectorcount - 2048;
	T0();
	for (i = 0; i < 2048; i++) {
		rdsect(fd, b0, sectorsize);
		b0++;
	}
	TN(2048);

	printf("\nTransfer rates:\n");
	printf("\toutside:     ");
	rdsect(fd, 0, sectorsize);
	T0();
	for (i = 0; i < bulk; i++) {
		rdmega(fd);
	}
	TR(bulk * 1024);

	printf("\tmiddle:      ");
	b0 = sectorcount / 2 - bulk * (1024*1024 / sectorsize) / 2 - 1;
	rdsect(fd, b0, sectorsize);
	T0();
	for (i = 0; i < bulk; i++) {
		rdmega(fd);
	}
	TR(bulk * 1024);

	printf("\tinside:      ");
	b0 = sectorcount - bulk * (1024*1024 / sectorsize) - 1;
	rdsect(fd, b0, sectorsize);
	T0();
	for (i = 0; i < bulk; i++) {
		rdmega(fd);
	}
	TR(bulk * 1024);

	printf("\n");
	return;
}