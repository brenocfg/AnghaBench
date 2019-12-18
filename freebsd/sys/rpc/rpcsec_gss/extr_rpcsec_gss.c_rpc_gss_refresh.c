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
struct TYPE_3__ {scalar_t__ rj_stat; scalar_t__ rj_why; } ;
struct TYPE_4__ {scalar_t__ rp_stat; TYPE_1__ rp_rjct; } ;
struct rpc_msg {TYPE_2__ rm_reply; } ;
struct rpc_gss_data {scalar_t__ gd_state; int /*<<< orphan*/  gd_lock; } ;
typedef  int /*<<< orphan*/  rpc_gss_options_ret_t ;
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 scalar_t__ AUTH_ERROR ; 
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSG_DENIED ; 
 scalar_t__ RPCSEC_GSS_CREDPROBLEM ; 
 scalar_t__ RPCSEC_GSS_CTXPROBLEM ; 
 scalar_t__ RPCSEC_GSS_DESTROYING ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gss_destroy_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
rpc_gss_refresh(AUTH *auth, void *msg)
{
	struct rpc_msg *reply = (struct rpc_msg *) msg;
	rpc_gss_options_ret_t options;
	struct rpc_gss_data *gd;

	gd = AUTH_PRIVATE(auth);
	
	/*
	 * If the context is in DESTROYING state, then just return, since
	 * there is no point in refreshing the credentials.
	 */
	mtx_lock(&gd->gd_lock);
	if (gd->gd_state == RPCSEC_GSS_DESTROYING) {
		mtx_unlock(&gd->gd_lock);
		return (FALSE);
	}
	mtx_unlock(&gd->gd_lock);

	/*
	 * If the error was RPCSEC_GSS_CREDPROBLEM of
	 * RPCSEC_GSS_CTXPROBLEM we start again from scratch. All
	 * other errors are fatal.
	 */
	if (reply->rm_reply.rp_stat == MSG_DENIED
	    && reply->rm_reply.rp_rjct.rj_stat == AUTH_ERROR
	    && (reply->rm_reply.rp_rjct.rj_why == RPCSEC_GSS_CREDPROBLEM
		|| reply->rm_reply.rp_rjct.rj_why == RPCSEC_GSS_CTXPROBLEM)) {
		rpc_gss_destroy_context(auth, FALSE);
		memset(&options, 0, sizeof(options));
		return (rpc_gss_init(auth, &options));
	}

	return (FALSE);
}