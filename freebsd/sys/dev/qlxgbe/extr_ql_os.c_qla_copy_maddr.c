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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 size_t Q8_MAC_ADDR_LEN ; 
 size_t Q8_MAX_NUM_MULTICAST_ADDRS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u_int
qla_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int mcnt)
{
	uint8_t *mta = arg;

	if (mcnt == Q8_MAX_NUM_MULTICAST_ADDRS)
		return (0);

	bcopy(LLADDR(sdl), &mta[mcnt * Q8_MAC_ADDR_LEN], Q8_MAC_ADDR_LEN);

	return (1);
}