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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtredirect_fib (struct sockaddr*,struct sockaddr*,struct sockaddr*,int,struct sockaddr*,int /*<<< orphan*/ ) ; 

void
in_rtredirect(struct sockaddr *dst,
	struct sockaddr *gateway,
	struct sockaddr *netmask,
	int flags,
	struct sockaddr *src,
	u_int fibnum)
{
	rtredirect_fib(dst, gateway, netmask, flags, src, fibnum);
}