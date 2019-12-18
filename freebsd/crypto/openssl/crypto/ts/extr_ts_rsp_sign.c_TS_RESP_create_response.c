#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * response; int /*<<< orphan*/ * tst_info; int /*<<< orphan*/ * request; } ;
typedef  TYPE_1__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  TS_RESP ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CREATE_RESPONSE ; 
 int /*<<< orphan*/  TS_INFO_BAD_DATA_FORMAT ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_failure_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TS_RESP_CTX_set_status_info_cond (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_RESP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_RESP_new () ; 
 int /*<<< orphan*/  TS_R_RESPONSE_SETUP_ERROR ; 
 int /*<<< orphan*/  TS_STATUS_GRANTED ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_TS_REQ_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_RESP_CTX_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_RESP_CTX_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_RESP_check_request (TYPE_1__*) ; 
 int /*<<< orphan*/ * ts_RESP_create_tst_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_RESP_get_policy (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_RESP_process_extensions (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_RESP_sign (TYPE_1__*) ; 

TS_RESP *TS_RESP_create_response(TS_RESP_CTX *ctx, BIO *req_bio)
{
    ASN1_OBJECT *policy;
    TS_RESP *response;
    int result = 0;

    ts_RESP_CTX_init(ctx);

    if ((ctx->response = TS_RESP_new()) == NULL) {
        TSerr(TS_F_TS_RESP_CREATE_RESPONSE, ERR_R_MALLOC_FAILURE);
        goto end;
    }
    if ((ctx->request = d2i_TS_REQ_bio(req_bio, NULL)) == NULL) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Bad request format or system error.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_BAD_DATA_FORMAT);
        goto end;
    }
    if (!TS_RESP_CTX_set_status_info(ctx, TS_STATUS_GRANTED, NULL))
        goto end;
    if (!ts_RESP_check_request(ctx))
        goto end;
    if ((policy = ts_RESP_get_policy(ctx)) == NULL)
        goto end;
    if ((ctx->tst_info = ts_RESP_create_tst_info(ctx, policy)) == NULL)
        goto end;
    if (!ts_RESP_process_extensions(ctx))
        goto end;
    if (!ts_RESP_sign(ctx))
        goto end;
    result = 1;

 end:
    if (!result) {
        TSerr(TS_F_TS_RESP_CREATE_RESPONSE, TS_R_RESPONSE_SETUP_ERROR);
        if (ctx->response != NULL) {
            if (TS_RESP_CTX_set_status_info_cond(ctx,
                                                 TS_STATUS_REJECTION,
                                                 "Error during response "
                                                 "generation.") == 0) {
                TS_RESP_free(ctx->response);
                ctx->response = NULL;
            }
        }
    }
    response = ctx->response;
    ctx->response = NULL;       /* Ownership will be returned to caller. */
    ts_RESP_CTX_cleanup(ctx);
    return response;
}