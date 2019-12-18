#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct TYPE_3__ {scalar_t__ num_mac; int /*<<< orphan*/ * mac; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
struct mbx_set_common_iface_multicast {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 scalar_t__ OCE_MAX_MC_FILTER_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
oce_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct mbx_set_common_iface_multicast *req = arg;

	if (req->params.req.num_mac == OCE_MAX_MC_FILTER_SIZE)
		return (0);

	bcopy(LLADDR(sdl), &req->params.req.mac[req->params.req.num_mac++],
	    ETHER_ADDR_LEN);

	return (1);
}