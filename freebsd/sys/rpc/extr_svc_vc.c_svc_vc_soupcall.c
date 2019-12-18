#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xp_socket; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int SU_OK ; 
 scalar_t__ soreadable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_active (TYPE_1__*) ; 

__attribute__((used)) static int
svc_vc_soupcall(struct socket *so, void *arg, int waitflag)
{
	SVCXPRT *xprt = (SVCXPRT *) arg;

	if (soreadable(xprt->xp_socket))
		xprt_active(xprt);
	return (SU_OK);
}