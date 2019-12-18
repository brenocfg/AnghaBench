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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_len; } ;
struct sockaddr {int dummy; } ;
struct qlnxr_dev {TYPE_2__* ha; } ;
struct llentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIPQUAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int arpresolve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ *,struct llentry**,...) ; 

__attribute__((used)) static int
qlnxr_addr4_resolve(struct qlnxr_dev *dev,
			      struct sockaddr_in *src_in,
			      struct sockaddr_in *dst_in,
			      u8 *dst_mac)
{
	int rc;

#if __FreeBSD_version >= 1100000
	rc = arpresolve(dev->ha->ifp, 0, NULL, (struct sockaddr *)dst_in,
			dst_mac, NULL, NULL);
#else
	struct llentry *lle;

	rc = arpresolve(dev->ha->ifp, NULL, NULL, (struct sockaddr *)dst_in,
			dst_mac, &lle);
#endif

	QL_DPRINT12(dev->ha, "rc = %d "
		"sa_len = 0x%x sa_family = 0x%x IP Address = %d.%d.%d.%d "
		"Dest MAC %02x:%02x:%02x:%02x:%02x:%02x\n", rc,
		dst_in->sin_len, dst_in->sin_family,
		NIPQUAD((dst_in->sin_addr.s_addr)),
		dst_mac[0], dst_mac[1], dst_mac[2],
		dst_mac[3], dst_mac[4], dst_mac[5]);

	return rc;
}