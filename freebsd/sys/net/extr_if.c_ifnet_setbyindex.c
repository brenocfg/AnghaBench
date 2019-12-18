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
typedef  size_t u_short ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct ifnet** V_ifindex_table ; 

__attribute__((used)) static void
ifnet_setbyindex(u_short idx, struct ifnet *ifp)
{

	V_ifindex_table[idx] = ifp;
}