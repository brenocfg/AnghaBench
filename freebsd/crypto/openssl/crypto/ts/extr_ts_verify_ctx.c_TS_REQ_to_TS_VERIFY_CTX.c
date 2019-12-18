#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_12__ {int /*<<< orphan*/ * hashed_msg; int /*<<< orphan*/ * hash_algo; } ;
struct TYPE_11__ {int /*<<< orphan*/ * nonce; TYPE_3__* msg_imprint; int /*<<< orphan*/ * policy_id; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/ * nonce; int /*<<< orphan*/  imprint_len; int /*<<< orphan*/ * imprint; int /*<<< orphan*/ * md_alg; int /*<<< orphan*/ * policy; } ;
typedef  TYPE_1__ TS_VERIFY_CTX ;
typedef  TYPE_2__ TS_REQ ;
typedef  TYPE_3__ TS_MSG_IMPRINT ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_free (TYPE_1__*) ; 
 TYPE_1__* TS_VERIFY_CTX_new () ; 
 int TS_VFY_ALL_IMPRINT ; 
 int TS_VFY_NONCE ; 
 int TS_VFY_POLICY ; 
 int TS_VFY_SIGNATURE ; 
 int TS_VFY_TSA_NAME ; 
 int /*<<< orphan*/ * X509_ALGOR_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TS_VERIFY_CTX *TS_REQ_to_TS_VERIFY_CTX(TS_REQ *req, TS_VERIFY_CTX *ctx)
{
    TS_VERIFY_CTX *ret = ctx;
    ASN1_OBJECT *policy;
    TS_MSG_IMPRINT *imprint;
    X509_ALGOR *md_alg;
    ASN1_OCTET_STRING *msg;
    const ASN1_INTEGER *nonce;

    OPENSSL_assert(req != NULL);
    if (ret)
        TS_VERIFY_CTX_cleanup(ret);
    else if ((ret = TS_VERIFY_CTX_new()) == NULL)
        return NULL;

    ret->flags = TS_VFY_ALL_IMPRINT & ~(TS_VFY_TSA_NAME | TS_VFY_SIGNATURE);

    if ((policy = req->policy_id) != NULL) {
        if ((ret->policy = OBJ_dup(policy)) == NULL)
            goto err;
    } else
        ret->flags &= ~TS_VFY_POLICY;

    imprint = req->msg_imprint;
    md_alg = imprint->hash_algo;
    if ((ret->md_alg = X509_ALGOR_dup(md_alg)) == NULL)
        goto err;
    msg = imprint->hashed_msg;
    ret->imprint_len = ASN1_STRING_length(msg);
    if ((ret->imprint = OPENSSL_malloc(ret->imprint_len)) == NULL)
        goto err;
    memcpy(ret->imprint, ASN1_STRING_get0_data(msg), ret->imprint_len);

    if ((nonce = req->nonce) != NULL) {
        if ((ret->nonce = ASN1_INTEGER_dup(nonce)) == NULL)
            goto err;
    } else
        ret->flags &= ~TS_VFY_NONCE;

    return ret;
 err:
    if (ctx)
        TS_VERIFY_CTX_cleanup(ctx);
    else
        TS_VERIFY_CTX_free(ret);
    return NULL;
}