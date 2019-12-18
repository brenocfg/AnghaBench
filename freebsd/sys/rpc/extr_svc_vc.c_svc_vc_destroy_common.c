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
struct TYPE_4__ {scalar_t__ xp_netid; scalar_t__ xp_socket; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  soclose (scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_1__*) ; 

__attribute__((used)) static void
svc_vc_destroy_common(SVCXPRT *xprt)
{

	if (xprt->xp_socket)
		(void)soclose(xprt->xp_socket);

	if (xprt->xp_netid)
		(void) mem_free(xprt->xp_netid, strlen(xprt->xp_netid) + 1);
	svc_xprt_free(xprt);
}