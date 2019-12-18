#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_2__ {scalar_t__ value; } ;
struct rpc_gss_data {int /*<<< orphan*/  gd_lock; TYPE_1__ gd_verf; int /*<<< orphan*/ * gd_clntprincipal; int /*<<< orphan*/ * gd_principal; int /*<<< orphan*/  gd_ucred; int /*<<< orphan*/  gd_clnt; int /*<<< orphan*/  gd_refs; } ;
typedef  struct rpc_gss_data AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (struct rpc_gss_data*) ; 
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_RPC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (struct rpc_gss_data*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gss_destroy_context (struct rpc_gss_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_gss_buffer_desc ; 

__attribute__((used)) static void
rpc_gss_destroy(AUTH *auth)
{
	struct rpc_gss_data	*gd;
	
	rpc_gss_log_debug("in rpc_gss_destroy()");
	
	gd = AUTH_PRIVATE(auth);
	
	if (!refcount_release(&gd->gd_refs))
		return;

	rpc_gss_destroy_context(auth, TRUE);
	
	CLNT_RELEASE(gd->gd_clnt);
	crfree(gd->gd_ucred);
	free(gd->gd_principal, M_RPC);
	if (gd->gd_clntprincipal != NULL)
		free(gd->gd_clntprincipal, M_RPC);
	if (gd->gd_verf.value)
		xdr_free((xdrproc_t) xdr_gss_buffer_desc,
		    (char *) &gd->gd_verf);
	mtx_destroy(&gd->gd_lock);

	mem_free(gd, sizeof(*gd));
	mem_free(auth, sizeof(*auth));
}