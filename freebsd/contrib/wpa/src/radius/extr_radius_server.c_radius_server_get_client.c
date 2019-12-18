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
struct radius_server_data {struct radius_client* clients; } ;
struct TYPE_8__ {int s_addr; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_6__ {int* s6_addr; } ;
struct TYPE_5__ {int* s6_addr; } ;
struct radius_client {struct radius_client* next; TYPE_4__ mask; TYPE_3__ addr; TYPE_2__ mask6; TYPE_1__ addr6; } ;
struct in_addr {int s_addr; } ;
struct in6_addr {int* s6_addr; } ;

/* Variables and functions */

__attribute__((used)) static struct radius_client *
radius_server_get_client(struct radius_server_data *data, struct in_addr *addr,
			 int ipv6)
{
	struct radius_client *client = data->clients;

	while (client) {
#ifdef CONFIG_IPV6
		if (ipv6) {
			struct in6_addr *addr6;
			int i;

			addr6 = (struct in6_addr *) addr;
			for (i = 0; i < 16; i++) {
				if ((addr6->s6_addr[i] &
				     client->mask6.s6_addr[i]) !=
				    (client->addr6.s6_addr[i] &
				     client->mask6.s6_addr[i])) {
					i = 17;
					break;
				}
			}
			if (i == 16) {
				break;
			}
		}
#endif /* CONFIG_IPV6 */
		if (!ipv6 && (client->addr.s_addr & client->mask.s_addr) ==
		    (addr->s_addr & client->mask.s_addr)) {
			break;
		}

		client = client->next;
	}

	return client;
}