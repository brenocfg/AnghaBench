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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int MAX_NUM_MULTICAST_ADDRESSES ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u_int
em_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	u8 *mta = arg;

	if (cnt == MAX_NUM_MULTICAST_ADDRESSES)
		return (1);

	bcopy(LLADDR(sdl), &mta[cnt * ETHER_ADDR_LEN], ETHER_ADDR_LEN);

	return (1);
}