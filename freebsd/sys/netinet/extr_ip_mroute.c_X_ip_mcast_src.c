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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  in_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ v_lcl_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  VIF_LOCK () ; 
 int /*<<< orphan*/  VIF_UNLOCK () ; 
 int V_numvifs ; 
 TYPE_2__* V_viftable ; 

__attribute__((used)) static u_long
X_ip_mcast_src(int vifi)
{
	in_addr_t addr;

	addr = INADDR_ANY;
	if (vifi < 0)
		return (addr);

	VIF_LOCK();
	if (vifi < V_numvifs)
		addr = V_viftable[vifi].v_lcl_addr.s_addr;
	VIF_UNLOCK();

	return (addr);
}