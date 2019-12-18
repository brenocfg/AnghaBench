#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int maxlen; struct svc_dg_data* buf; } ;
struct svc_dg_data {int su_iosz; TYPE_1__ su_srcaddr; int /*<<< orphan*/  su_xdrs; } ;
struct TYPE_12__ {int maxlen; struct svc_dg_data* buf; } ;
struct TYPE_11__ {int maxlen; struct svc_dg_data* buf; } ;
struct TYPE_13__ {int xp_fd; int /*<<< orphan*/  xp_tp; TYPE_3__ xp_ltaddr; TYPE_2__ xp_rtaddr; } ;
typedef  TYPE_4__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (struct svc_dg_data*,int) ; 
 struct svc_dg_data* rpc_buffer (TYPE_4__*) ; 
 struct svc_dg_data* su_data (TYPE_4__*) ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_4__*) ; 
 int /*<<< orphan*/  xprt_unregister (TYPE_4__*) ; 

__attribute__((used)) static void
svc_dg_destroy(SVCXPRT *xprt)
{
	struct svc_dg_data *su = su_data(xprt);

	xprt_unregister(xprt);
	if (xprt->xp_fd != -1)
		(void)_close(xprt->xp_fd);
	XDR_DESTROY(&(su->su_xdrs));
	(void) mem_free(rpc_buffer(xprt), su->su_iosz);
	if (su->su_srcaddr.buf)
		(void) mem_free(su->su_srcaddr.buf, su->su_srcaddr.maxlen);
	(void) mem_free(su, sizeof (*su));
	if (xprt->xp_rtaddr.buf)
		(void) mem_free(xprt->xp_rtaddr.buf, xprt->xp_rtaddr.maxlen);
	if (xprt->xp_ltaddr.buf)
		(void) mem_free(xprt->xp_ltaddr.buf, xprt->xp_ltaddr.maxlen);
	free(xprt->xp_tp);
	svc_xprt_free(xprt);
}