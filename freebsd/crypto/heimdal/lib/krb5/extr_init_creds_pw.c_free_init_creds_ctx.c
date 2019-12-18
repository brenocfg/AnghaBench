#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* krb5_init_creds_context ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {struct TYPE_7__* ppaid; int /*<<< orphan*/  as_req; int /*<<< orphan*/  error; int /*<<< orphan*/  enc_part; int /*<<< orphan*/  as_rep; int /*<<< orphan*/  md; int /*<<< orphan*/  cred; int /*<<< orphan*/  req_buffer; struct TYPE_7__* password; struct TYPE_7__* keytab_data; struct TYPE_7__* in_tkt_service; struct TYPE_7__* pre_auth_types; struct TYPE_7__* etypes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_AS_REP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_AS_REQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_EncKDCRepPart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_KRB_ERROR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_METHOD_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_paid (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strlen (TYPE_1__*) ; 

__attribute__((used)) static void
free_init_creds_ctx(krb5_context context, krb5_init_creds_context ctx)
{
    if (ctx->etypes)
	free(ctx->etypes);
    if (ctx->pre_auth_types)
	free (ctx->pre_auth_types);
    if (ctx->in_tkt_service)
	free(ctx->in_tkt_service);
    if (ctx->keytab_data)
	free(ctx->keytab_data);
    if (ctx->password) {
	memset(ctx->password, 0, strlen(ctx->password));
	free(ctx->password);
    }
    krb5_data_free(&ctx->req_buffer);
    krb5_free_cred_contents(context, &ctx->cred);
    free_METHOD_DATA(&ctx->md);
    free_AS_REP(&ctx->as_rep);
    free_EncKDCRepPart(&ctx->enc_part);
    free_KRB_ERROR(&ctx->error);
    free_AS_REQ(&ctx->as_req);
    if (ctx->ppaid) {
	free_paid(context, ctx->ppaid);
	free(ctx->ppaid);
    }
    memset(ctx, 0, sizeof(*ctx));
}