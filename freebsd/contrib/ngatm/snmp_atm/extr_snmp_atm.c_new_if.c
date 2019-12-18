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
struct TYPE_3__ {scalar_t__ ifi_type; } ;
struct TYPE_4__ {TYPE_1__ ifmd_data; } ;
struct mibif {int /*<<< orphan*/ * xnotify; TYPE_2__ mib; } ;

/* Variables and functions */
 scalar_t__ IFT_ATM ; 
 int /*<<< orphan*/  attach_if (struct mibif*) ; 
 int /*<<< orphan*/  started ; 

__attribute__((used)) static int
new_if(struct mibif *ifp)
{
	if (!started || ifp->mib.ifmd_data.ifi_type != IFT_ATM ||
	    ifp->xnotify != NULL)
		return (0);

	attach_if(ifp);
	return (1);
}