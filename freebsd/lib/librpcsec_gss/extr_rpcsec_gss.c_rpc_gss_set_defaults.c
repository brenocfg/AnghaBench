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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  gc_svc; } ;
struct rpc_gss_data {int /*<<< orphan*/  gd_qop; TYPE_1__ gd_cred; int /*<<< orphan*/  gd_mech; } ;
typedef  int /*<<< orphan*/  rpc_gss_service_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  rpc_gss_oid_to_mech (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  rpc_gss_qop_to_num (char const*,char const*,int /*<<< orphan*/ *) ; 

bool_t
rpc_gss_set_defaults(AUTH *auth, rpc_gss_service_t service, const char *qop)
{
	struct rpc_gss_data	*gd;
	u_int			qop_num;
	const char		*mechanism;

	gd = AUTH_PRIVATE(auth);
	if (!rpc_gss_oid_to_mech(gd->gd_mech, &mechanism)) {
		return (FALSE);
	}

	if (qop) {
		if (!rpc_gss_qop_to_num(qop, mechanism, &qop_num)) {
			return (FALSE);
		}
	} else {
		qop_num = GSS_C_QOP_DEFAULT;
	}

	gd->gd_cred.gc_svc = service;
	gd->gd_qop = qop_num;
	return (TRUE);
}