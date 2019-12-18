#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ifnet {int dummy; } ;
struct TYPE_7__ {struct ifnet* ifp; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int ETHER_HDR_LEN ; 
 int /*<<< orphan*/  QLNX_LOCK (TYPE_1__*) ; 
 int QLNX_MAX_NUM_MULTICAST_ADDRS ; 
 int /*<<< orphan*/  QLNX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_copy_maddr ; 
 int /*<<< orphan*/  qlnx_hw_set_multi (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 

__attribute__((used)) static int
qlnx_set_multi(qlnx_host_t *ha, uint32_t add_multi)
{
	uint8_t		mta[QLNX_MAX_NUM_MULTICAST_ADDRS * ETHER_HDR_LEN];
	struct ifnet	*ifp = ha->ifp;
	u_int		mcnt;

	if (qlnx_vf_device(ha) == 0)
		return (0);

	mcnt = if_foreach_llmaddr(ifp, qlnx_copy_maddr, mta);

	QLNX_LOCK(ha);
	qlnx_hw_set_multi(ha, mta, mcnt, add_multi);
	QLNX_UNLOCK(ha);

	return (0);
}