#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct pa_info_data {int /*<<< orphan*/ * s2kparams; int /*<<< orphan*/  salt; void* etype; } ;
typedef  int /*<<< orphan*/  paid ;
typedef  int /*<<< orphan*/  krb5_krbhst_info ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
struct TYPE_16__ {scalar_t__ keyseed; int /*<<< orphan*/  req_buffer; int /*<<< orphan*/  pk_nonce; scalar_t__ pk_init_ctx; struct pa_info_data* ppaid; } ;
typedef  TYPE_3__ krb5_get_init_creds_ctx ;
typedef  scalar_t__ krb5_error_code ;
typedef  void* krb5_enctype ;
struct TYPE_17__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_4__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_14__ {void* etype; } ;
struct TYPE_19__ {TYPE_8__* padata; TYPE_1__ enc_part; } ;
struct TYPE_15__ {int /*<<< orphan*/  realm; } ;
struct TYPE_18__ {TYPE_2__ req_body; } ;
typedef  int /*<<< orphan*/  PA_DATA ;
typedef  TYPE_5__ AS_REQ ;
typedef  TYPE_6__ AS_REP ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  KRB5_PADATA_PK_AS_REP ; 
 int /*<<< orphan*/  KRB5_PADATA_PK_AS_REP_19 ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ _krb5_pk_rd_pa_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_paid (int /*<<< orphan*/ ,struct pa_info_data*) ; 
 int /*<<< orphan*/ * krb5_find_padata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ krb5_get_pw_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pa_info_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pa_data_to_key_plain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ; 
 struct pa_info_data* process_pa_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,struct pa_info_data*,TYPE_8__*) ; 

__attribute__((used)) static krb5_error_code
process_pa_data_to_key(krb5_context context,
		       krb5_get_init_creds_ctx *ctx,
		       krb5_creds *creds,
		       AS_REQ *a,
		       AS_REP *rep,
		       const krb5_krbhst_info *hi,
		       krb5_keyblock **key)
{
    struct pa_info_data paid, *ppaid = NULL;
    krb5_error_code ret;
    krb5_enctype etype;
    PA_DATA *pa;

    memset(&paid, 0, sizeof(paid));

    etype = rep->enc_part.etype;

    if (rep->padata) {
	paid.etype = etype;
	ppaid = process_pa_info(context, creds->client, a, &paid,
				rep->padata);
    }
    if (ppaid == NULL)
	ppaid = ctx->ppaid;
    if (ppaid == NULL) {
	ret = krb5_get_pw_salt (context, creds->client, &paid.salt);
	if (ret)
	    return ret;
	paid.etype = etype;
	paid.s2kparams = NULL;
	ppaid = &paid;
    }

    pa = NULL;
    if (rep->padata) {
	int idx = 0;
	pa = krb5_find_padata(rep->padata->val,
			      rep->padata->len,
			      KRB5_PADATA_PK_AS_REP,
			      &idx);
	if (pa == NULL) {
	    idx = 0;
	    pa = krb5_find_padata(rep->padata->val,
				  rep->padata->len,
				  KRB5_PADATA_PK_AS_REP_19,
				  &idx);
	}
    }
    if (pa && ctx->pk_init_ctx) {
#ifdef PKINIT
	_krb5_debug(context, 5, "krb5_get_init_creds: using PKINIT");

	ret = _krb5_pk_rd_pa_reply(context,
				   a->req_body.realm,
				   ctx->pk_init_ctx,
				   etype,
				   hi,
				   ctx->pk_nonce,
				   &ctx->req_buffer,
				   pa,
				   key);
#else
	ret = EINVAL;
	krb5_set_error_message(context, ret, N_("no support for PKINIT compiled in", ""));
#endif
    } else if (ctx->keyseed) {
 	_krb5_debug(context, 5, "krb5_get_init_creds: using keyproc");
	ret = pa_data_to_key_plain(context, creds->client, ctx,
				   ppaid->salt, ppaid->s2kparams, etype, key);
    } else {
	ret = EINVAL;
	krb5_set_error_message(context, ret, N_("No usable pa data type", ""));
    }

    free_paid(context, &paid);
    return ret;
}