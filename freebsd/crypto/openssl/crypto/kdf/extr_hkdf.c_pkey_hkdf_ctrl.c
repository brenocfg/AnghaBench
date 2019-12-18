#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int mode; int salt_len; int key_len; int info_len; int info; int /*<<< orphan*/ * key; int /*<<< orphan*/ * salt; void* md; } ;
typedef  TYPE_1__ HKDF_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
#define  EVP_PKEY_CTRL_HKDF_INFO 132 
#define  EVP_PKEY_CTRL_HKDF_KEY 131 
#define  EVP_PKEY_CTRL_HKDF_MD 130 
#define  EVP_PKEY_CTRL_HKDF_MODE 129 
#define  EVP_PKEY_CTRL_HKDF_SALT 128 
 int HKDF_MAXBUF ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,int) ; 
 void* OPENSSL_memdup (void*,int) ; 
 int /*<<< orphan*/  memcpy (int,void*,int) ; 

__attribute__((used)) static int pkey_hkdf_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    HKDF_PKEY_CTX *kctx = ctx->data;

    switch (type) {
    case EVP_PKEY_CTRL_HKDF_MD:
        if (p2 == NULL)
            return 0;

        kctx->md = p2;
        return 1;

    case EVP_PKEY_CTRL_HKDF_MODE:
        kctx->mode = p1;
        return 1;

    case EVP_PKEY_CTRL_HKDF_SALT:
        if (p1 == 0 || p2 == NULL)
            return 1;

        if (p1 < 0)
            return 0;

        if (kctx->salt != NULL)
            OPENSSL_clear_free(kctx->salt, kctx->salt_len);

        kctx->salt = OPENSSL_memdup(p2, p1);
        if (kctx->salt == NULL)
            return 0;

        kctx->salt_len = p1;
        return 1;

    case EVP_PKEY_CTRL_HKDF_KEY:
        if (p1 < 0)
            return 0;

        if (kctx->key != NULL)
            OPENSSL_clear_free(kctx->key, kctx->key_len);

        kctx->key = OPENSSL_memdup(p2, p1);
        if (kctx->key == NULL)
            return 0;

        kctx->key_len  = p1;
        return 1;

    case EVP_PKEY_CTRL_HKDF_INFO:
        if (p1 == 0 || p2 == NULL)
            return 1;

        if (p1 < 0 || p1 > (int)(HKDF_MAXBUF - kctx->info_len))
            return 0;

        memcpy(kctx->info + kctx->info_len, p2, p1);
        kctx->info_len += p1;
        return 1;

    default:
        return -2;

    }
}