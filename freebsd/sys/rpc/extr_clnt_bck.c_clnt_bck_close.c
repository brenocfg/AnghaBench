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
struct ct_data {int /*<<< orphan*/  ct_lock; scalar_t__ ct_closed; scalar_t__ ct_closing; } ;
struct TYPE_3__ {scalar_t__ cl_private; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  msleep (struct ct_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ct_data*) ; 

__attribute__((used)) static void
clnt_bck_close(CLIENT *cl)
{
	struct ct_data *ct = (struct ct_data *) cl->cl_private;

	mtx_lock(&ct->ct_lock);

	if (ct->ct_closed) {
		mtx_unlock(&ct->ct_lock);
		return;
	}

	if (ct->ct_closing) {
		while (ct->ct_closing)
			msleep(ct, &ct->ct_lock, 0, "rpcclose", 0);
		KASSERT(ct->ct_closed, ("client should be closed"));
		mtx_unlock(&ct->ct_lock);
		return;
	}

	ct->ct_closing = FALSE;
	ct->ct_closed = TRUE;
	mtx_unlock(&ct->ct_lock);
	wakeup(ct);
}