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
struct ifaddr {scalar_t__ ifa_carp; } ;

/* Variables and functions */
 scalar_t__ carp_master_p (struct ifaddr*) ; 
 scalar_t__ stub1 (struct ifaddr*) ; 
 scalar_t__ stub2 (struct ifaddr*) ; 

int
ifa_preferred(struct ifaddr *cur, struct ifaddr *next)
{

	return (cur->ifa_carp && (!next->ifa_carp ||
	    ((*carp_master_p)(next) && !(*carp_master_p)(cur))));
}