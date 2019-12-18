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
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  __svc_vc_dodestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svc_vc_destroy(SVCXPRT *xprt)
{
	assert(xprt != NULL);
	
	xprt_unregister(xprt);
	__svc_vc_dodestroy(xprt);
}