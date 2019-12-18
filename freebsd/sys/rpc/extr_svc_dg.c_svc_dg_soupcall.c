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
struct socket {int dummy; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int SU_OK ; 
 int /*<<< orphan*/  xprt_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
svc_dg_soupcall(struct socket *so, void *arg, int waitflag)
{
	SVCXPRT *xprt = (SVCXPRT *) arg;

	xprt_active(xprt);
	return (SU_OK);
}