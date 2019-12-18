#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct rpc_pending_request {int dummy; } ;
struct TYPE_3__ {scalar_t__ length; } ;
struct TYPE_4__ {TYPE_1__ gc_handle; int /*<<< orphan*/  gc_proc; } ;
struct rpc_gss_data {scalar_t__ gd_state; scalar_t__ gd_ctx; int /*<<< orphan*/  gd_lock; TYPE_2__ gd_cred; int /*<<< orphan*/  gd_reqs; int /*<<< orphan*/  gd_clnt; } ;
struct rpc_callextra {int /*<<< orphan*/ * rc_auth; } ;
typedef  int /*<<< orphan*/  ext ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTH_TIMEOUT ; 
 int /*<<< orphan*/  CLNT_CALL_EXT (int /*<<< orphan*/ ,struct rpc_callextra*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 struct rpc_pending_request* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct rpc_pending_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULLPROC ; 
 int /*<<< orphan*/  RPCSEC_GSS_DESTROY ; 
 scalar_t__ RPCSEC_GSS_DESTROYING ; 
 scalar_t__ RPCSEC_GSS_ESTABLISHED ; 
 scalar_t__ RPCSEC_GSS_START ; 
 int /*<<< orphan*/  bzero (struct rpc_callextra*,int) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_free (struct rpc_pending_request*,int) ; 
 int /*<<< orphan*/  msleep (struct rpc_gss_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_link ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 int /*<<< orphan*/  wakeup (struct rpc_gss_data*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_gss_buffer_desc ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
rpc_gss_destroy_context(AUTH *auth, bool_t send_destroy)
{
	struct rpc_gss_data	*gd;
	struct rpc_pending_request *pr;
	OM_uint32		 min_stat;
	struct rpc_callextra	 ext;

	rpc_gss_log_debug("in rpc_gss_destroy_context()");
	
	gd = AUTH_PRIVATE(auth);
	
	mtx_lock(&gd->gd_lock);
	/*
	 * If the context isn't in ESTABISHED state, someone else is
	 * destroying/refreshing - we wait till they are done.
	 */
	if (gd->gd_state != RPCSEC_GSS_ESTABLISHED) {
		while (gd->gd_state != RPCSEC_GSS_START
		    && gd->gd_state != RPCSEC_GSS_ESTABLISHED)
			msleep(gd, &gd->gd_lock, 0, "gssstate", 0);
		mtx_unlock(&gd->gd_lock);
		return;
	}
	gd->gd_state = RPCSEC_GSS_DESTROYING;
	mtx_unlock(&gd->gd_lock);

	if (send_destroy) {
		gd->gd_cred.gc_proc = RPCSEC_GSS_DESTROY;
		bzero(&ext, sizeof(ext));
		ext.rc_auth = auth;
		CLNT_CALL_EXT(gd->gd_clnt, &ext, NULLPROC,
		    (xdrproc_t)xdr_void, NULL,
		    (xdrproc_t)xdr_void, NULL, AUTH_TIMEOUT);
	}

	while ((pr = LIST_FIRST(&gd->gd_reqs)) != NULL) {
		LIST_REMOVE(pr, pr_link);
		mem_free(pr, sizeof(*pr));
	}

	/*
	 * Free the context token. Remember that this was
	 * allocated by XDR, not GSS-API.
	 */
	xdr_free((xdrproc_t) xdr_gss_buffer_desc,
	    (char *) &gd->gd_cred.gc_handle);
	gd->gd_cred.gc_handle.length = 0;

	if (gd->gd_ctx != GSS_C_NO_CONTEXT)
		gss_delete_sec_context(&min_stat, &gd->gd_ctx, NULL);

	mtx_lock(&gd->gd_lock);
	gd->gd_state = RPCSEC_GSS_START;
	wakeup(gd);
	mtx_unlock(&gd->gd_lock);
}