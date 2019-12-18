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
typedef  int in_addr_t ;

/* Variables and functions */

__attribute__((used)) static in_addr_t
choose_ipaddr(in_addr_t **alist, in_addr_t net, in_addr_t netmask)
{

	for (; *alist; ++alist)
		if ((**alist & netmask) == net)
			return **alist;
	return 0;
}