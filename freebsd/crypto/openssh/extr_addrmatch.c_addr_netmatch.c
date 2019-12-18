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
typedef  int /*<<< orphan*/  u_int ;
struct xaddr {scalar_t__ af; } ;

/* Variables and functions */
 int addr_and (struct xaddr*,struct xaddr const*,struct xaddr*) ; 
 int addr_cmp (struct xaddr*,struct xaddr const*) ; 
 int addr_netmask (scalar_t__,int /*<<< orphan*/ ,struct xaddr*) ; 

__attribute__((used)) static int
addr_netmatch(const struct xaddr *host, const struct xaddr *net, u_int masklen)
{
	struct xaddr tmp_mask, tmp_result;

	if (host->af != net->af)
		return -1;

	if (addr_netmask(host->af, masklen, &tmp_mask) == -1)
		return -1;
	if (addr_and(&tmp_result, host, &tmp_mask) == -1)
		return -1;
	return addr_cmp(&tmp_result, net);
}