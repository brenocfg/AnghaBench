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
typedef  scalar_t__ uint32_t ;
struct ifnet {scalar_t__ if_mtu; } ;
struct adapter {scalar_t__ max_frame_size; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOCTL_DEBUGOUT (char*) ; 
 scalar_t__ IXGBE_MAX_FRAME_SIZE ; 
 scalar_t__ IXGBE_MTU_HDR ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixv_if_mtu_set(if_ctx_t ctx, uint32_t mtu)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct ifnet   *ifp = iflib_get_ifp(ctx);
	int            error = 0;

	IOCTL_DEBUGOUT("ioctl: SIOCSIFMTU (Set Interface MTU)");
	if (mtu > IXGBE_MAX_FRAME_SIZE - IXGBE_MTU_HDR) {
		error = EINVAL;
	} else {
		ifp->if_mtu = mtu;
		adapter->max_frame_size = ifp->if_mtu + IXGBE_MTU_HDR;
	}

	return error;
}