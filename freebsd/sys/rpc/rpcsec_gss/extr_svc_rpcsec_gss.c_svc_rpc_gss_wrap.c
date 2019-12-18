#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_rpc_gss_cookedcred {scalar_t__ cc_service; int /*<<< orphan*/  cc_seq; struct svc_rpc_gss_client* cc_client; } ;
struct svc_rpc_gss_client {scalar_t__ cl_state; int /*<<< orphan*/  cl_qop; int /*<<< orphan*/  cl_ctx; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ svc_ah_private; } ;
typedef  TYPE_1__ SVCAUTH ;

/* Variables and functions */
 scalar_t__ CLIENT_ESTABLISHED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 scalar_t__ rpc_gss_svc_none ; 
 int /*<<< orphan*/  xdr_rpc_gss_wrap_data (struct mbuf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
svc_rpc_gss_wrap(SVCAUTH *auth, struct mbuf **mp)
{
	struct svc_rpc_gss_cookedcred *cc;
	struct svc_rpc_gss_client *client;
	
	rpc_gss_log_debug("in svc_rpc_gss_wrap()");

	cc = (struct svc_rpc_gss_cookedcred *) auth->svc_ah_private;
	client = cc->cc_client;
	if (client->cl_state != CLIENT_ESTABLISHED
	    || cc->cc_service == rpc_gss_svc_none || *mp == NULL) {
		return (TRUE);
	}
	
	return (xdr_rpc_gss_wrap_data(mp,
		client->cl_ctx, client->cl_qop,
		cc->cc_service, cc->cc_seq));
}