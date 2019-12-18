#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
struct TYPE_4__ {scalar_t__ service; } ;
struct svc_rpc_gss_client {scalar_t__ cl_state; int /*<<< orphan*/  cl_seq; TYPE_1__ cl_rawcred; int /*<<< orphan*/  cl_qop; int /*<<< orphan*/  cl_ctx; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_5__ {scalar_t__ svc_ah_private; } ;
typedef  TYPE_2__ SVCAUTH ;

/* Variables and functions */
 scalar_t__ CLIENT_ESTABLISHED ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 scalar_t__ rpc_gss_svc_none ; 
 int /*<<< orphan*/  xdr_rpc_gss_unwrap_data (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bool_t
svc_rpc_gss_unwrap(SVCAUTH *auth, XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr)
{
	struct svc_rpc_gss_client *client;

	log_debug("in svc_rpc_gss_unwrap()");
	
	client = (struct svc_rpc_gss_client *) auth->svc_ah_private;
	if (client->cl_state != CLIENT_ESTABLISHED
	    || client->cl_rawcred.service == rpc_gss_svc_none) {
		return xdr_func(xdrs, xdr_ptr);
	}
	return (xdr_rpc_gss_unwrap_data(xdrs, xdr_func, xdr_ptr,
		client->cl_ctx, client->cl_qop,
		client->cl_rawcred.service, client->cl_seq));
}