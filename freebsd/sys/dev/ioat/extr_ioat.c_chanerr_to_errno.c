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
typedef  int uint32_t ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int IOAT_CHANERR_NDADDERR ; 
 int IOAT_CHANERR_RDERR ; 
 int IOAT_CHANERR_WDERR ; 
 int IOAT_CHANERR_XDADDERR ; 
 int IOAT_CHANERR_XSADDERR ; 

__attribute__((used)) static int
chanerr_to_errno(uint32_t chanerr)
{

	if (chanerr == 0)
		return (0);
	if ((chanerr & (IOAT_CHANERR_XSADDERR | IOAT_CHANERR_XDADDERR)) != 0)
		return (EFAULT);
	if ((chanerr & (IOAT_CHANERR_RDERR | IOAT_CHANERR_WDERR)) != 0)
		return (EIO);
	/* This one is probably our fault: */
	if ((chanerr & IOAT_CHANERR_NDADDERR) != 0)
		return (EIO);
	return (EIO);
}