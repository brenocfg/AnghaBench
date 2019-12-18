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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_LINK ; 
 int /*<<< orphan*/  ipfw_unhook (int /*<<< orphan*/ ) ; 

void
ipfw_detach_hooks(void)
{

	ipfw_unhook(AF_INET);
#ifdef INET6
	ipfw_unhook(AF_INET6);
#endif
	ipfw_unhook(AF_LINK);
}