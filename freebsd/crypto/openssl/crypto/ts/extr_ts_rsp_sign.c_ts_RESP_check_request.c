#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_14__ {scalar_t__ length; } ;
struct TYPE_13__ {TYPE_5__* hashed_msg; TYPE_1__* hash_algo; } ;
struct TYPE_12__ {TYPE_4__* msg_imprint; } ;
struct TYPE_11__ {int /*<<< orphan*/  mds; TYPE_3__* request; } ;
typedef  TYPE_2__ TS_RESP_CTX ;
typedef  TYPE_3__ TS_REQ ;
typedef  TYPE_4__ TS_MSG_IMPRINT ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_5__ ASN1_OCTET_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_TYPE_get (scalar_t__) ; 
 scalar_t__ EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_INFO_BAD_ALG ; 
 int /*<<< orphan*/  TS_INFO_BAD_DATA_FORMAT ; 
 int /*<<< orphan*/  TS_INFO_BAD_REQUEST ; 
 int TS_REQ_get_version (TYPE_3__*) ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_failure_info (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 scalar_t__ V_ASN1_NULL ; 
 int sk_EVP_MD_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_EVP_MD_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ts_RESP_check_request(TS_RESP_CTX *ctx)
{
    TS_REQ *request = ctx->request;
    TS_MSG_IMPRINT *msg_imprint;
    X509_ALGOR *md_alg;
    int md_alg_id;
    const ASN1_OCTET_STRING *digest;
    const EVP_MD *md = NULL;
    int i;

    if (TS_REQ_get_version(request) != 1) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Bad request version.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_BAD_REQUEST);
        return 0;
    }

    msg_imprint = request->msg_imprint;
    md_alg = msg_imprint->hash_algo;
    md_alg_id = OBJ_obj2nid(md_alg->algorithm);
    for (i = 0; !md && i < sk_EVP_MD_num(ctx->mds); ++i) {
        const EVP_MD *current_md = sk_EVP_MD_value(ctx->mds, i);
        if (md_alg_id == EVP_MD_type(current_md))
            md = current_md;
    }
    if (!md) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Message digest algorithm is "
                                    "not supported.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_BAD_ALG);
        return 0;
    }

    if (md_alg->parameter && ASN1_TYPE_get(md_alg->parameter) != V_ASN1_NULL) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Superfluous message digest "
                                    "parameter.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_BAD_ALG);
        return 0;
    }
    digest = msg_imprint->hashed_msg;
    if (digest->length != EVP_MD_size(md)) {
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Bad message digest.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_BAD_DATA_FORMAT);
        return 0;
    }

    return 1;
}