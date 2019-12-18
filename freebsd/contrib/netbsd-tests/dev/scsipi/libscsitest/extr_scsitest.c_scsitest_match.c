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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cfdata_t ;

/* Variables and functions */
 int CDBLOCKSIZE ; 
 int /*<<< orphan*/  MYCDISO ; 
 int RUMPUSER_FT_REG ; 
 int /*<<< orphan*/  RUMPUSER_OPEN_RDWR ; 
 int isofd ; 
 int mycdsize ; 
 scalar_t__ rumpuser_getfileinfo (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int rumpuser_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
scsitest_match(device_t parent, cfdata_t match, void *aux)
{
#ifdef USE_TOSI_ISO
	uint64_t fsize;
	int error, ft;

	if (rumpuser_getfileinfo(MYCDISO, &fsize, &ft, &error))
		return 0;
	if (ft != RUMPUSER_FT_REG)
		return 0;
	mycdsize = fsize / CDBLOCKSIZE;

	if ((isofd = rumpuser_open(MYCDISO, RUMPUSER_OPEN_RDWR, &error)) == -1)
		return 0;
#else
	/*
	 * We pretend to have a medium present initially, so != -1.
	 */
	isofd = -2;
#endif

	return 1;
}