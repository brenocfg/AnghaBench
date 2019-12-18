#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rfc5114_param; scalar_t__ param_nid; int /*<<< orphan*/  generator; int /*<<< orphan*/  prime_len; scalar_t__ use_dsa; } ;
struct TYPE_6__ {scalar_t__ pkey_gencb; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DSA ;
typedef  TYPE_2__ DH_PKEY_CTX ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int DH_generate_parameters_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_get_1024_160 () ; 
 int /*<<< orphan*/ * DH_get_2048_224 () ; 
 int /*<<< orphan*/ * DH_get_2048_256 () ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/ * DH_new_by_nid (scalar_t__) ; 
 int /*<<< orphan*/ * DSA_dup_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_DH ; 
 int /*<<< orphan*/  EVP_PKEY_DHX ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsa_dh_generate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evp_pkey_set_cb_translate (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int pkey_dh_paramgen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    DH *dh = NULL;
    DH_PKEY_CTX *dctx = ctx->data;
    BN_GENCB *pcb;
    int ret;
    if (dctx->rfc5114_param) {
        switch (dctx->rfc5114_param) {
        case 1:
            dh = DH_get_1024_160();
            break;

        case 2:
            dh = DH_get_2048_224();
            break;

        case 3:
            dh = DH_get_2048_256();
            break;

        default:
            return -2;
        }
        EVP_PKEY_assign(pkey, EVP_PKEY_DHX, dh);
        return 1;
    }

    if (dctx->param_nid != 0) {
        if ((dh = DH_new_by_nid(dctx->param_nid)) == NULL)
            return 0;
        EVP_PKEY_assign(pkey, EVP_PKEY_DH, dh);
        return 1;
    }

    if (ctx->pkey_gencb) {
        pcb = BN_GENCB_new();
        if (pcb == NULL)
            return 0;
        evp_pkey_set_cb_translate(pcb, ctx);
    } else
        pcb = NULL;
#ifndef OPENSSL_NO_DSA
    if (dctx->use_dsa) {
        DSA *dsa_dh;
        dsa_dh = dsa_dh_generate(dctx, pcb);
        BN_GENCB_free(pcb);
        if (dsa_dh == NULL)
            return 0;
        dh = DSA_dup_DH(dsa_dh);
        DSA_free(dsa_dh);
        if (!dh)
            return 0;
        EVP_PKEY_assign(pkey, EVP_PKEY_DHX, dh);
        return 1;
    }
#endif
    dh = DH_new();
    if (dh == NULL) {
        BN_GENCB_free(pcb);
        return 0;
    }
    ret = DH_generate_parameters_ex(dh,
                                    dctx->prime_len, dctx->generator, pcb);
    BN_GENCB_free(pcb);
    if (ret)
        EVP_PKEY_assign_DH(pkey, dh);
    else
        DH_free(dh);
    return ret;
}