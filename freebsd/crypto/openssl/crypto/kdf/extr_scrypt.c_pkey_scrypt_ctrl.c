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
typedef  int uint64_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int N; int r; int p; int maxmem_bytes; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; } ;
typedef  TYPE_1__ SCRYPT_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
#define  EVP_PKEY_CTRL_PASS 133 
#define  EVP_PKEY_CTRL_SCRYPT_MAXMEM_BYTES 132 
#define  EVP_PKEY_CTRL_SCRYPT_N 131 
#define  EVP_PKEY_CTRL_SCRYPT_P 130 
#define  EVP_PKEY_CTRL_SCRYPT_R 129 
#define  EVP_PKEY_CTRL_SCRYPT_SALT 128 
 int /*<<< orphan*/  is_power_of_two (int) ; 
 int pkey_scrypt_set_membuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int pkey_scrypt_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    SCRYPT_PKEY_CTX *kctx = ctx->data;
    uint64_t u64_value;

    switch (type) {
    case EVP_PKEY_CTRL_PASS:
        return pkey_scrypt_set_membuf(&kctx->pass, &kctx->pass_len, p2, p1);

    case EVP_PKEY_CTRL_SCRYPT_SALT:
        return pkey_scrypt_set_membuf(&kctx->salt, &kctx->salt_len, p2, p1);

    case EVP_PKEY_CTRL_SCRYPT_N:
        u64_value = *((uint64_t *)p2);
        if ((u64_value <= 1) || !is_power_of_two(u64_value))
            return 0;
        kctx->N = u64_value;
        return 1;

    case EVP_PKEY_CTRL_SCRYPT_R:
        u64_value = *((uint64_t *)p2);
        if (u64_value < 1)
            return 0;
        kctx->r = u64_value;
        return 1;

    case EVP_PKEY_CTRL_SCRYPT_P:
        u64_value = *((uint64_t *)p2);
        if (u64_value < 1)
            return 0;
        kctx->p = u64_value;
        return 1;

    case EVP_PKEY_CTRL_SCRYPT_MAXMEM_BYTES:
        u64_value = *((uint64_t *)p2);
        if (u64_value < 1)
            return 0;
        kctx->maxmem_bytes = u64_value;
        return 1;

    default:
        return -2;

    }
}