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
typedef  int /*<<< orphan*/  tmp_addr ;
struct xaddr {int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int addr_and (struct xaddr*,struct xaddr*,struct xaddr*) ; 
 int addr_hostmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xaddr*) ; 
 int addr_is_all0s (struct xaddr*) ; 
 int /*<<< orphan*/  memcpy (struct xaddr*,struct xaddr const*,int) ; 

__attribute__((used)) static int
addr_host_is_all0s(const struct xaddr *a, u_int masklen)
{
	struct xaddr tmp_addr, tmp_mask, tmp_result;

	memcpy(&tmp_addr, a, sizeof(tmp_addr));
	if (addr_hostmask(a->af, masklen, &tmp_mask) == -1)
		return (-1);
	if (addr_and(&tmp_result, &tmp_addr, &tmp_mask) == -1)
		return (-1);
	return (addr_is_all0s(&tmp_result));
}