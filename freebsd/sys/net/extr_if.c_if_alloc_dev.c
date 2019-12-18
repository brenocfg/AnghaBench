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
typedef  int /*<<< orphan*/  u_char ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int IF_NODOM ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ *,int*) ; 
 struct ifnet* if_alloc_domain (int /*<<< orphan*/ ,int) ; 

struct ifnet *
if_alloc_dev(u_char type, device_t dev)
{
	int numa_domain;

	if (dev == NULL || bus_get_domain(dev, &numa_domain) != 0)
		return (if_alloc_domain(type, IF_NODOM));
	return (if_alloc_domain(type, numa_domain));
}