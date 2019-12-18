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
struct vnet {int dummy; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct mtuex_arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (struct vnet*) ; 
 int /*<<< orphan*/  MTUTIMO_DEFAULT ; 
 int /*<<< orphan*/  V_rtq_mtutimer ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 int /*<<< orphan*/  in6_mtuexpire ; 
 int /*<<< orphan*/  in6_mtutimo_setwa ; 
 int /*<<< orphan*/  rt_foreach_fib_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtuex_arg*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static void
in6_mtutimo(void *rock)
{
	CURVNET_SET_QUIET((struct vnet *) rock);
	struct timeval atv;
	struct mtuex_arg arg;

	rt_foreach_fib_walk(AF_INET6, in6_mtutimo_setwa, in6_mtuexpire, &arg);

	atv.tv_sec = MTUTIMO_DEFAULT;
	atv.tv_usec = 0;
	callout_reset(&V_rtq_mtutimer, tvtohz(&atv), in6_mtutimo, rock);
	CURVNET_RESTORE();
}