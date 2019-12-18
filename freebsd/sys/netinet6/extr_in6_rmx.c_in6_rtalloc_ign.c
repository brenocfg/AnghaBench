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
typedef  int /*<<< orphan*/  u_int ;
struct route_in6 {int dummy; } ;
struct route {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtalloc_ign_fib (struct route*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
in6_rtalloc_ign(struct route_in6 *ro, u_long ignflags, u_int fibnum)
{

	rtalloc_ign_fib((struct route *)ro, ignflags, fibnum);
}