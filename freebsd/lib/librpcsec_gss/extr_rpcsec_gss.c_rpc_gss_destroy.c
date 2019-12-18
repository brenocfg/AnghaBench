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
struct rpc_gss_data {scalar_t__ gd_name; TYPE_1__ gd_verf; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  struct rpc_gss_data AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (struct rpc_gss_data*) ; 
 scalar_t__ GSS_C_NO_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  mem_free (struct rpc_gss_data*,int) ; 
 int /*<<< orphan*/  rpc_gss_destroy_context (struct rpc_gss_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_gss_buffer_desc ; 

__attribute__((used)) static void
rpc_gss_destroy(AUTH *auth)
{
	struct rpc_gss_data	*gd;
	OM_uint32		 min_stat;
	
	log_debug("in rpc_gss_destroy()");
	
	gd = AUTH_PRIVATE(auth);
	
	rpc_gss_destroy_context(auth, TRUE);
	
	if (gd->gd_name != GSS_C_NO_NAME)
		gss_release_name(&min_stat, &gd->gd_name);
	if (gd->gd_verf.value)
		xdr_free((xdrproc_t) xdr_gss_buffer_desc,
		    (char *) &gd->gd_verf);

	mem_free(gd, sizeof(*gd));
	mem_free(auth, sizeof(*auth));
}