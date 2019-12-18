#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct delete_sec_context_res {int /*<<< orphan*/  output_token; } ;
struct delete_sec_context_args {scalar_t__ ctx; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_ctx_id_t ;
typedef  TYPE_2__* gss_buffer_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_9__ {int /*<<< orphan*/ * value; scalar_t__ length; } ;
struct TYPE_8__ {scalar_t__ handle; } ;
typedef  int OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct delete_sec_context_res*,int) ; 
 int gssd_delete_sec_context_1 (struct delete_sec_context_args*,struct delete_sec_context_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_copy_buffer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kgss_delete_context (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 int /*<<< orphan*/  kgss_gssd_handle ; 
 scalar_t__ xdr_delete_sec_context_res ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct delete_sec_context_res*) ; 

OM_uint32
gss_delete_sec_context(OM_uint32 *minor_status, gss_ctx_id_t *context_handle,
	gss_buffer_t output_token)
{
	struct delete_sec_context_res res;
	struct delete_sec_context_args args;
	enum clnt_stat stat;
	gss_ctx_id_t ctx;
	CLIENT *cl;

	*minor_status = 0;

	if (!kgss_gssd_handle)
		return (GSS_S_FAILURE);

	if (*context_handle) {
		ctx = *context_handle;

		/*
		 * If we are past the context establishment phase, let
		 * the in-kernel code do the delete, otherwise
		 * userland needs to deal with it.
		 */
		if (ctx->handle) {
			args.ctx = ctx->handle;
			cl = kgss_gssd_client();
			if (cl == NULL)
				return (GSS_S_FAILURE);
	
			bzero(&res, sizeof(res));
			stat = gssd_delete_sec_context_1(&args, &res, cl);
			CLNT_RELEASE(cl);
			if (stat != RPC_SUCCESS) {
				*minor_status = stat;
				return (GSS_S_FAILURE);
			}

			if (output_token)
				kgss_copy_buffer(&res.output_token,
				    output_token);
			xdr_free((xdrproc_t) xdr_delete_sec_context_res, &res);

			kgss_delete_context(ctx, NULL);
		} else {
			kgss_delete_context(ctx, output_token);
		}
		*context_handle = NULL;
	} else {
		if (output_token) {
			output_token->length = 0;
			output_token->value = NULL;
		}
	}

	return (GSS_S_COMPLETE);
}