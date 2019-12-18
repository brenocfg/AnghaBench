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
struct rtentry {int dummy; } ;

/* Variables and functions */
 int rtrequest_fib (int,struct sockaddr*,struct sockaddr*,struct sockaddr*,int,struct rtentry**,int /*<<< orphan*/ ) ; 

int
in6_rtrequest(int req, struct sockaddr *dst, struct sockaddr *gw,
    struct sockaddr *mask, int flags, struct rtentry **ret_nrt, u_int fibnum)
{

	return (rtrequest_fib(req, dst, gw, mask, flags, ret_nrt, fibnum));
}