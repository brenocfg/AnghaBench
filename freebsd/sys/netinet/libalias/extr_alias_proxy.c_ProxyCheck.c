#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_char ;
struct in_addr {scalar_t__ s_addr; } ;
struct TYPE_8__ {int s_addr; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct proxy_entry {scalar_t__ proxy_port; scalar_t__ proto; scalar_t__ server_port; int proxy_type; struct proxy_entry* next; struct in_addr server_addr; TYPE_4__ dst_addr; TYPE_3__ src_addr; TYPE_2__ dst_mask; TYPE_1__ src_mask; } ;
struct libalias {struct proxy_entry* proxyList; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 

int
ProxyCheck(struct libalias *la, struct in_addr *proxy_server_addr,
    u_short * proxy_server_port, struct in_addr src_addr, 
    struct in_addr dst_addr, u_short dst_port, u_char ip_p)
{
	struct proxy_entry *ptr;

	LIBALIAS_LOCK_ASSERT(la);

	ptr = la->proxyList;
	while (ptr != NULL) {
		u_short proxy_port;

		proxy_port = ptr->proxy_port;
		if ((dst_port == proxy_port || proxy_port == 0)
		    && ip_p == ptr->proto
		    && src_addr.s_addr != ptr->server_addr.s_addr) {
			struct in_addr src_addr_masked;
			struct in_addr dst_addr_masked;

			src_addr_masked.s_addr = src_addr.s_addr & ptr->src_mask.s_addr;
			dst_addr_masked.s_addr = dst_addr.s_addr & ptr->dst_mask.s_addr;

			if ((src_addr_masked.s_addr == ptr->src_addr.s_addr)
			    && (dst_addr_masked.s_addr == ptr->dst_addr.s_addr)) {
				if ((*proxy_server_port = ptr->server_port) == 0)
					*proxy_server_port = dst_port;
				*proxy_server_addr = ptr->server_addr;
				return (ptr->proxy_type);
			}
		}
		ptr = ptr->next;
	}

	return (0);
}