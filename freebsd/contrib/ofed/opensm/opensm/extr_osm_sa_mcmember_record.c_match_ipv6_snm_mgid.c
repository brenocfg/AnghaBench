#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int prefix; int interface_id; } ;
struct TYPE_5__ {TYPE_1__ unicast; } ;
typedef  TYPE_2__ ib_gid_t ;

/* Variables and functions */
 int INT_ID_MASK ; 
 int INT_ID_SIGNATURE ; 
 int PREFIX_MASK ; 
 int PREFIX_SIGNATURE ; 

__attribute__((used)) static unsigned match_ipv6_snm_mgid(ib_gid_t * mgid)
{
	return ((mgid->unicast.prefix & PREFIX_MASK) == PREFIX_SIGNATURE &&
		(mgid->unicast.interface_id & INT_ID_MASK) == INT_ID_SIGNATURE);
}