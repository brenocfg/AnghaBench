#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct acm_ep_addr_data {TYPE_1__ info; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_EP_INFO_ADDRESS_IP ; 
 int /*<<< orphan*/  ACM_EP_INFO_ADDRESS_IP6 ; 
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ucma_set_ep_addr(struct acm_ep_addr_data *data, struct sockaddr *addr)
{
	if (addr->sa_family == AF_INET) {
		data->type = ACM_EP_INFO_ADDRESS_IP;
		memcpy(data->info.addr, &((struct sockaddr_in *) addr)->sin_addr, 4);
	} else {
		data->type = ACM_EP_INFO_ADDRESS_IP6;
		memcpy(data->info.addr, &((struct sockaddr_in6 *) addr)->sin6_addr, 16);
	}
}