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
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 scalar_t__ IN_LOCAL_GROUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_igmp_sendlocal ; 
 scalar_t__ in_allhosts (struct in_addr const) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
igmp_isgroupreported(const struct in_addr addr)
{

	if (in_allhosts(addr) ||
	    ((!V_igmp_sendlocal && IN_LOCAL_GROUP(ntohl(addr.s_addr)))))
		return (0);

	return (1);
}