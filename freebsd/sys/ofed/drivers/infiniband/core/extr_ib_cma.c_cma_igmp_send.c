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
typedef  union ib_gid {int dummy; } ib_gid ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct net_device {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int if_addmulti (struct net_device*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int if_delmulti (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  rdma_gid2ip (struct sockaddr*,union ib_gid const*) ; 

__attribute__((used)) static int cma_igmp_send(struct net_device *ndev, const union ib_gid *mgid, bool join)
{
	int retval;

	if (ndev) {
		union {
			struct sockaddr sock;
			struct sockaddr_storage storage;
		} addr;

		rdma_gid2ip(&addr.sock, mgid);

		CURVNET_SET_QUIET(ndev->if_vnet);
		if (join)
			retval = -if_addmulti(ndev, &addr.sock, NULL);
		else
			retval = -if_delmulti(ndev, &addr.sock);
		CURVNET_RESTORE();
	} else {
		retval = -ENODEV;
	}
	return retval;
}