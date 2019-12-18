#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  saltvalue; int /*<<< orphan*/  salttype; } ;
struct pa_info_data {int /*<<< orphan*/ * s2kparams; TYPE_3__ salt; int /*<<< orphan*/  etype; } ;
typedef  TYPE_3__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_12__ {int /*<<< orphan*/ * keyseed; int /*<<< orphan*/ * keyproc; } ;
typedef  TYPE_4__ krb5_get_init_creds_ctx ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_9__ {int len; int /*<<< orphan*/ * val; } ;
struct TYPE_10__ {TYPE_1__ etype; } ;
struct TYPE_13__ {TYPE_2__ req_body; } ;
typedef  int /*<<< orphan*/  METHOD_DATA ;
typedef  TYPE_5__ AS_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  add_enc_ts_padata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
pa_data_to_md_ts_enc(krb5_context context,
		     const AS_REQ *a,
		     const krb5_principal client,
		     krb5_get_init_creds_ctx *ctx,
		     struct pa_info_data *ppaid,
		     METHOD_DATA *md)
{
    if (ctx->keyproc == NULL || ctx->keyseed == NULL)
	return 0;

    if (ppaid) {
	add_enc_ts_padata(context, md, client,
			  ctx->keyproc, ctx->keyseed,
			  &ppaid->etype, 1,
			  &ppaid->salt, ppaid->s2kparams);
    } else {
	krb5_salt salt;

	_krb5_debug(context, 5, "krb5_get_init_creds: pa-info not found, guessing salt");

	/* make a v5 salted pa-data */
	add_enc_ts_padata(context, md, client,
			  ctx->keyproc, ctx->keyseed,
			  a->req_body.etype.val, a->req_body.etype.len,
			  NULL, NULL);

	/* make a v4 salted pa-data */
	salt.salttype = KRB5_PW_SALT;
	krb5_data_zero(&salt.saltvalue);
	add_enc_ts_padata(context, md, client,
			  ctx->keyproc, ctx->keyseed,
			  a->req_body.etype.val, a->req_body.etype.len,
			  &salt, NULL);
    }
    return 0;
}