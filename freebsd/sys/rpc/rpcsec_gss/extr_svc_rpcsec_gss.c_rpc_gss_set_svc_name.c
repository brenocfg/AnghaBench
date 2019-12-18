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
typedef  void* u_int ;
struct svc_rpc_gss_svc_name {int /*<<< orphan*/  sn_principal; void* sn_version; void* sn_program; int /*<<< orphan*/  sn_cred; void* sn_req_time; int /*<<< orphan*/  sn_mech; } ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  M_RPC ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct svc_rpc_gss_svc_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svc_rpc_gss_svc_name* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (struct svc_rpc_gss_svc_name*,int) ; 
 int /*<<< orphan*/  rpc_gss_acquire_svc_cred (struct svc_rpc_gss_svc_name*) ; 
 int /*<<< orphan*/  rpc_gss_mech_to_oid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_link ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rpc_gss_lock ; 
 int /*<<< orphan*/  svc_rpc_gss_svc_names ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

bool_t
rpc_gss_set_svc_name(const char *principal, const char *mechanism,
    u_int req_time, u_int program, u_int version)
{
	struct svc_rpc_gss_svc_name *sname;
	gss_OID			mech_oid;

	if (!rpc_gss_mech_to_oid(mechanism, &mech_oid))
		return (FALSE);

	sname = mem_alloc(sizeof(*sname));
	if (!sname)
		return (FALSE);
	sname->sn_principal = strdup(principal, M_RPC);
	sname->sn_mech = mech_oid;
	sname->sn_req_time = req_time;
	sname->sn_cred = GSS_C_NO_CREDENTIAL;
	sname->sn_program = program;
	sname->sn_version = version;

	if (!rpc_gss_acquire_svc_cred(sname)) {
		free(sname->sn_principal, M_RPC);
		mem_free(sname, sizeof(*sname));
		return (FALSE);
	}

	sx_xlock(&svc_rpc_gss_lock);
	SLIST_INSERT_HEAD(&svc_rpc_gss_svc_names, sname, sn_link);
	sx_xunlock(&svc_rpc_gss_lock);

	return (TRUE);
}