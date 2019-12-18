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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ LIO_MAX_MULTICAST_ADDR ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
lio_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint64_t *mc = arg;

	if (cnt == LIO_MAX_MULTICAST_ADDR)
		return (0);

	mc += cnt;
	*mc = 0;
	memcpy(((uint8_t *)mc) + 2, LLADDR(sdl), ETHER_ADDR_LEN);
	/* no need to swap bytes */

	return (1);
}