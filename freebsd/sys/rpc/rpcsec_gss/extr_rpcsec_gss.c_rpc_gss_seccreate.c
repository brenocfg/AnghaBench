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
typedef  int /*<<< orphan*/  u_int ;
struct ucred {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_gss_service_t ;
typedef  int /*<<< orphan*/  rpc_gss_options_ret_t ;
typedef  int /*<<< orphan*/  rpc_gss_options_req_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  CLIENT ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  rpc_gss_mech_to_oid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gss_qop_to_num (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rpc_gss_seccreate_int (int /*<<< orphan*/ *,struct ucred*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

AUTH *
rpc_gss_seccreate(CLIENT *clnt, struct ucred *cred, const char *clnt_principal,
    const char *principal, const char *mechanism, rpc_gss_service_t service,
    const char *qop, rpc_gss_options_req_t *options_req,
    rpc_gss_options_ret_t *options_ret)
{
	gss_OID			oid;
	u_int			qop_num;

	/*
	 * Bail out now if we don't know this mechanism.
	 */
	if (!rpc_gss_mech_to_oid(mechanism, &oid))
		return (NULL);

	if (qop) {
		if (!rpc_gss_qop_to_num(qop, mechanism, &qop_num))
			return (NULL);
	} else {
		qop_num = GSS_C_QOP_DEFAULT;
	}

	return (rpc_gss_seccreate_int(clnt, cred, clnt_principal, principal,
		oid, service, qop_num, options_req, options_ret));
}