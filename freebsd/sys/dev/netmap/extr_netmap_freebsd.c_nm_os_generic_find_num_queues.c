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
typedef  unsigned int u_int ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int netmap_generic_rings ; 

void
nm_os_generic_find_num_queues(struct ifnet *ifp, u_int *txq, u_int *rxq)
{
	unsigned num_rings = netmap_generic_rings ? netmap_generic_rings : 1;

	*txq = num_rings;
	*rxq = num_rings;
}