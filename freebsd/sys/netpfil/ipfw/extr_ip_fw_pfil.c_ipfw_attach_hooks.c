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
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,scalar_t__*) ; 
 scalar_t__ V_fw6_enable ; 
 scalar_t__ V_fw_enable ; 
 scalar_t__ V_fwlink_enable ; 
 int /*<<< orphan*/  ipfw_hook (int /*<<< orphan*/ ) ; 
 int ipfw_link (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ipfw_attach_hooks(void)
{
	int error = 0;

	ipfw_hook(AF_INET);
	TUNABLE_INT_FETCH("net.inet.ip.fw.enable", &V_fw_enable);
	if (V_fw_enable && (error = ipfw_link(AF_INET, false)) != 0)
                printf("ipfw_hook() error\n");
#ifdef INET6
	ipfw_hook(AF_INET6);
	TUNABLE_INT_FETCH("net.inet6.ip6.fw.enable", &V_fw6_enable);
	if (V_fw6_enable && (error = ipfw_link(AF_INET6, false)) != 0)
                printf("ipfw6_hook() error\n");
#endif
	ipfw_hook(AF_LINK);
	TUNABLE_INT_FETCH("net.link.ether.ipfw", &V_fwlink_enable);
	if (V_fwlink_enable && (error = ipfw_link(AF_LINK, false)) != 0)
                printf("ipfw_link_hook() error\n");

	return (error);
}