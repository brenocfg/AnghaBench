#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_5__ {int /*<<< orphan*/  pk_nonce; int /*<<< orphan*/  ic_flags; int /*<<< orphan*/ * pk_init_ctx; } ;
typedef  TYPE_1__ krb5_get_init_creds_ctx ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int /*<<< orphan*/  req_body; } ;
typedef  int /*<<< orphan*/  METHOD_DATA ;
typedef  TYPE_2__ AS_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  _krb5_pk_mk_padata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
pa_data_to_md_pkinit(krb5_context context,
		     const AS_REQ *a,
		     const krb5_principal client,
		     int win2k,
		     krb5_get_init_creds_ctx *ctx,
		     METHOD_DATA *md)
{
    if (ctx->pk_init_ctx == NULL)
	return 0;
#ifdef PKINIT
    return _krb5_pk_mk_padata(context,
			      ctx->pk_init_ctx,
			      ctx->ic_flags,
			      win2k,
			      &a->req_body,
			      ctx->pk_nonce,
			      md);
#else
    krb5_set_error_message(context, EINVAL,
			   N_("no support for PKINIT compiled in", ""));
    return EINVAL;
#endif
}