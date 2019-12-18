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
struct TYPE_2__ {int gc_svc; } ;
struct rpc_gss_data {int /*<<< orphan*/  gd_mech; int /*<<< orphan*/  gd_qop; int /*<<< orphan*/  gd_ctx; TYPE_1__ gd_cred; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int TRUE ; 
 scalar_t__ gss_wrap_size_limit (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  rpc_gss_log_status (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
#define  rpc_gss_svc_default 131 
#define  rpc_gss_svc_integrity 130 
#define  rpc_gss_svc_none 129 
#define  rpc_gss_svc_privacy 128 

int
rpc_gss_max_data_length(AUTH *auth, int max_tp_unit_len)
{
	struct rpc_gss_data	*gd;
	int			want_conf;
	OM_uint32		max;
	OM_uint32		maj_stat, min_stat;
	int			result;

	gd = AUTH_PRIVATE(auth);

	switch (gd->gd_cred.gc_svc) {
	case rpc_gss_svc_none:
		return (max_tp_unit_len);
		break;

	case rpc_gss_svc_default:
	case rpc_gss_svc_integrity:
		want_conf = FALSE;
		break;

	case rpc_gss_svc_privacy:
		want_conf = TRUE;
		break;

	default:
		return (0);
	}

	maj_stat = gss_wrap_size_limit(&min_stat, gd->gd_ctx, want_conf,
	    gd->gd_qop, max_tp_unit_len, &max);

	if (maj_stat == GSS_S_COMPLETE) {
		result = (int) max;
		if (result < 0)
			result = 0;
		return (result);
	} else {
		rpc_gss_log_status("gss_wrap_size_limit", gd->gd_mech,
		    maj_stat, min_stat);
		return (0);
	}
}