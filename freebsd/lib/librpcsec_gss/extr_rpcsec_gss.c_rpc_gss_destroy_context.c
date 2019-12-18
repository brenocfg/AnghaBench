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
struct TYPE_3__ {scalar_t__ length; } ;
struct TYPE_4__ {TYPE_1__ gc_handle; int /*<<< orphan*/  gc_proc; } ;
struct rpc_gss_data {scalar_t__ gd_state; scalar_t__ gd_ctx; TYPE_2__ gd_cred; int /*<<< orphan*/  gd_clnt; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTH_TIMEOUT ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  NULLPROC ; 
 int /*<<< orphan*/  RPCSEC_GSS_DESTROY ; 
 scalar_t__ RPCSEC_GSS_ESTABLISHED ; 
 scalar_t__ RPCSEC_GSS_START ; 
 int /*<<< orphan*/  clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_gss_buffer_desc ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
rpc_gss_destroy_context(AUTH *auth, bool_t send_destroy)
{
	struct rpc_gss_data	*gd;
	OM_uint32		 min_stat;

	log_debug("in rpc_gss_destroy_context()");
	
	gd = AUTH_PRIVATE(auth);
	
	if (gd->gd_state == RPCSEC_GSS_ESTABLISHED && send_destroy) {
		gd->gd_cred.gc_proc = RPCSEC_GSS_DESTROY;
		clnt_call(gd->gd_clnt, NULLPROC,
		    (xdrproc_t)xdr_void, NULL,
		    (xdrproc_t)xdr_void, NULL, AUTH_TIMEOUT);
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

	gd->gd_state = RPCSEC_GSS_START;
}