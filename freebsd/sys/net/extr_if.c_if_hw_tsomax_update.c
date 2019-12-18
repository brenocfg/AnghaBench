#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet_hw_tsomax {scalar_t__ tsomaxbytes; scalar_t__ tsomaxsegsize; scalar_t__ tsomaxsegcount; } ;
typedef  TYPE_1__* if_t ;
struct TYPE_3__ {scalar_t__ if_hw_tsomax; scalar_t__ if_hw_tsomaxsegsize; scalar_t__ if_hw_tsomaxsegcount; } ;

/* Variables and functions */

int
if_hw_tsomax_update(if_t ifp, struct ifnet_hw_tsomax *pmax)
{
	int retval = 0;
	if (ifp->if_hw_tsomax != pmax->tsomaxbytes) {
		ifp->if_hw_tsomax = pmax->tsomaxbytes;
		retval++;
	}
	if (ifp->if_hw_tsomaxsegsize != pmax->tsomaxsegsize) {
		ifp->if_hw_tsomaxsegsize = pmax->tsomaxsegsize;
		retval++;
	}
	if (ifp->if_hw_tsomaxsegcount != pmax->tsomaxsegcount) {
		ifp->if_hw_tsomaxsegcount = pmax->tsomaxsegcount;
		retval++;
	}
	return (retval);
}