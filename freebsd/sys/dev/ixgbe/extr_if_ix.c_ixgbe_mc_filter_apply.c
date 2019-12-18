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
typedef  size_t u_int ;
struct sockaddr_dl {int dummy; } ;
struct ixgbe_mc_addr {int /*<<< orphan*/  vmdq; int /*<<< orphan*/  addr; } ;
struct adapter {int /*<<< orphan*/  pool; struct ixgbe_mc_addr* mta; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ETH_LENGTH_OF_ADDRESS ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 size_t MAX_NUM_MULTICAST_ADDRESSES ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
ixgbe_mc_filter_apply(void *arg, struct sockaddr_dl *sdl, u_int count)
{
	struct adapter *adapter = arg;
	struct ixgbe_mc_addr *mta = adapter->mta;

	if (count == MAX_NUM_MULTICAST_ADDRESSES)
		return (0);
	bcopy(LLADDR(sdl), mta[count].addr, IXGBE_ETH_LENGTH_OF_ADDRESS);
	mta[count].vmdq = adapter->pool;

	return (1);
}