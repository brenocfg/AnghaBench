#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nt_name; } ;
struct TYPE_4__ {TYPE_1__ gt_net; int /*<<< orphan*/ * gt_addrinfo; } ;
struct grouplist {scalar_t__ gr_type; TYPE_2__ gr_ptr; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ GT_HOST ; 
 scalar_t__ GT_NET ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_grp(struct grouplist *grp)
{
	if (grp->gr_type == GT_HOST) {
		if (grp->gr_ptr.gt_addrinfo != NULL)
			freeaddrinfo(grp->gr_ptr.gt_addrinfo);
	} else if (grp->gr_type == GT_NET) {
		if (grp->gr_ptr.gt_net.nt_name)
			free(grp->gr_ptr.gt_net.nt_name);
	}
	free((caddr_t)grp);
}