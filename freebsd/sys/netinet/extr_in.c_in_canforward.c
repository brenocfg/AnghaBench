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
typedef  int /*<<< orphan*/  u_long ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 scalar_t__ IN_EXPERIMENTAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_LINKLOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_LOOPBACK (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_MULTICAST (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_ZERONET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

int
in_canforward(struct in_addr in)
{
	u_long i = ntohl(in.s_addr);

	if (IN_EXPERIMENTAL(i) || IN_MULTICAST(i) || IN_LINKLOCAL(i) ||
	    IN_ZERONET(i) || IN_LOOPBACK(i))
		return (0);
	return (1);
}