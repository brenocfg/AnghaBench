#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {TYPE_1__* interfaces; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* for_each_interface ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  count_interface_cb ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int interface_count(struct hostapd_iface *iface)
{
	int count = 0;
	if (iface->interfaces == NULL ||
	    iface->interfaces->for_each_interface == NULL)
		return 0;
	iface->interfaces->for_each_interface(iface->interfaces,
					      count_interface_cb, &count);
	return count;
}