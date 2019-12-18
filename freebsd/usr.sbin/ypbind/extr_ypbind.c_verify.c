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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int RESTRICTED_SERVERS ; 
 int /*<<< orphan*/  bcmp (struct in_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * restricted_addrs ; 

int
verify(struct in_addr addr)
{
	int i;

	for (i = 0; i < RESTRICTED_SERVERS; i++)
		if (!bcmp(&addr, &restricted_addrs[i], sizeof(struct in_addr)))
			return(0);

	return(1);
}