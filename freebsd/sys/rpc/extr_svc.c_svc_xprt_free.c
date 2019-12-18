#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* xp_p3; } ;
typedef  int /*<<< orphan*/  SVCXPRT_EXT ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (TYPE_1__*,int) ; 

void
svc_xprt_free(SVCXPRT *xprt)
{

	mem_free(xprt->xp_p3, sizeof(SVCXPRT_EXT));
	mem_free(xprt, sizeof(SVCXPRT));
}