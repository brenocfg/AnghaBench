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
struct sockaddr {int dummy; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELETE ; 
 int ifa_maintain_loopback_route (int /*<<< orphan*/ ,char*,struct ifaddr*,struct sockaddr*) ; 

int
ifa_del_loopback_route(struct ifaddr *ifa, struct sockaddr *ia)
{

	return (ifa_maintain_loopback_route(RTM_DELETE, "deletion", ifa, ia));
}