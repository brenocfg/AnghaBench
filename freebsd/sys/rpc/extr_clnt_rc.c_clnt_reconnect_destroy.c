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
struct rc_data {int /*<<< orphan*/  rc_lock; int /*<<< orphan*/  rc_ucred; scalar_t__ rc_backchannel; scalar_t__ rc_client; scalar_t__ cl_private; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  struct rc_data CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_DESTROY (scalar_t__) ; 
 int /*<<< orphan*/  SVC_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (struct rc_data*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clnt_reconnect_destroy(CLIENT *cl)
{
	struct rc_data *rc = (struct rc_data *)cl->cl_private;
	SVCXPRT *xprt;

	if (rc->rc_client)
		CLNT_DESTROY(rc->rc_client);
	if (rc->rc_backchannel) {
		xprt = (SVCXPRT *)rc->rc_backchannel;
		xprt_unregister(xprt);
		SVC_RELEASE(xprt);
	}
	crfree(rc->rc_ucred);
	mtx_destroy(&rc->rc_lock);
	mem_free(rc, sizeof(*rc));
	mem_free(cl, sizeof (CLIENT));
}