#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  md; int /*<<< orphan*/  id_set; int /*<<< orphan*/  id_len; int /*<<< orphan*/ * id; int /*<<< orphan*/ * gen_group; } ;
typedef  TYPE_1__ SM2_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_GROUP_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM2_F_PKEY_SM2_COPY ; 
 int /*<<< orphan*/  SM2err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_sm2_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  pkey_sm2_init (TYPE_2__*) ; 

__attribute__((used)) static int pkey_sm2_copy(EVP_PKEY_CTX *dst, EVP_PKEY_CTX *src)
{
    SM2_PKEY_CTX *dctx, *sctx;

    if (!pkey_sm2_init(dst))
        return 0;
    sctx = src->data;
    dctx = dst->data;
    if (sctx->gen_group != NULL) {
        dctx->gen_group = EC_GROUP_dup(sctx->gen_group);
        if (dctx->gen_group == NULL) {
            pkey_sm2_cleanup(dst);
            return 0;
        }
    }
    if (sctx->id != NULL) {
        dctx->id = OPENSSL_malloc(sctx->id_len);
        if (dctx->id == NULL) {
            SM2err(SM2_F_PKEY_SM2_COPY, ERR_R_MALLOC_FAILURE);
            pkey_sm2_cleanup(dst);
            return 0;
        }
        memcpy(dctx->id, sctx->id, sctx->id_len);
    }
    dctx->id_len = sctx->id_len;
    dctx->id_set = sctx->id_set;
    dctx->md = sctx->md;

    return 1;
}