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
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/ * ifa_ifwithaddr (struct sockaddr const*) ; 

int
ifa_ifwithaddr_check(const struct sockaddr *addr)
{
	struct epoch_tracker et;
	int rc;

	NET_EPOCH_ENTER(et);
	rc = (ifa_ifwithaddr(addr) != NULL);
	NET_EPOCH_EXIT(et);
	return (rc);
}