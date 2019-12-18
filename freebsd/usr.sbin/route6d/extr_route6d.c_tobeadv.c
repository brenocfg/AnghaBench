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
struct riprt {int rrt_flags; scalar_t__ rrt_index; } ;
struct ifc {scalar_t__ ifc_index; } ;

/* Variables and functions */
 int RTF_BLACKHOLE ; 
 int RTF_REJECT ; 
 int RTF_STATIC ; 
 scalar_t__ Sflag ; 
 scalar_t__ hflag ; 
 scalar_t__ sflag ; 

__attribute__((used)) static int
tobeadv(struct riprt *rrt, struct ifc *ifcp)
{

	/* Special care for static routes */
	if (rrt->rrt_flags & RTF_STATIC) {
		/* XXX don't advertise reject/blackhole routes */
		if (rrt->rrt_flags & (RTF_REJECT | RTF_BLACKHOLE))
			return 0;

		if (Sflag)	/* Yes, advertise it anyway */
			return 1;
		if (sflag && rrt->rrt_index != ifcp->ifc_index)
			return 1;
		return 0;
	}
	/* Regular split horizon */
	if (hflag == 0 && rrt->rrt_index == ifcp->ifc_index)
		return 0;
	return 1;
}