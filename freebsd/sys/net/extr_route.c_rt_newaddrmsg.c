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
struct rtentry {int dummy; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_ALL_FIBS ; 
 int /*<<< orphan*/  rt_newaddrmsg_fib (int,struct ifaddr*,int,struct rtentry*,int /*<<< orphan*/ ) ; 

void
rt_newaddrmsg(int cmd, struct ifaddr *ifa, int error, struct rtentry *rt)
{

	rt_newaddrmsg_fib(cmd, ifa, error, rt, RT_ALL_FIBS);
}