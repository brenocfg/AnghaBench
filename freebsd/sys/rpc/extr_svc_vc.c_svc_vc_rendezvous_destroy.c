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
struct TYPE_4__ {int /*<<< orphan*/  xp_socket; scalar_t__ xp_upcallset; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  SOLISTEN_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLISTEN_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solisten_upcall_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_vc_destroy_common (TYPE_1__*) ; 

__attribute__((used)) static void
svc_vc_rendezvous_destroy(SVCXPRT *xprt)
{

	SOLISTEN_LOCK(xprt->xp_socket);
	if (xprt->xp_upcallset) {
		xprt->xp_upcallset = 0;
		solisten_upcall_set(xprt->xp_socket, NULL, NULL);
	}
	SOLISTEN_UNLOCK(xprt->xp_socket);

	svc_vc_destroy_common(xprt);
}