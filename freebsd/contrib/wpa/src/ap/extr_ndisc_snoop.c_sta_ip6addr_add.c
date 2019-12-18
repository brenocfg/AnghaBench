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
struct sta_info {int /*<<< orphan*/  ip6addr; } ;
struct ip6addr {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 struct ip6addr* os_zalloc (int) ; 

__attribute__((used)) static int sta_ip6addr_add(struct sta_info *sta, struct in6_addr *addr)
{
	struct ip6addr *ip6addr;

	ip6addr = os_zalloc(sizeof(*ip6addr));
	if (!ip6addr)
		return -1;

	os_memcpy(&ip6addr->addr, addr, sizeof(*addr));

	dl_list_add_tail(&sta->ip6addr, &ip6addr->list);

	return 0;
}