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
struct TYPE_7__ {unsigned int buf_len; int flags; int* buf; TYPE_1__* cipher; int /*<<< orphan*/  encrypt; } ;
struct TYPE_6__ {int flags; int (* do_cipher ) (TYPE_2__*,unsigned char*,int*,unsigned int) ;unsigned int block_size; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPH_FLAG_CUSTOM_CIPHER ; 
 int EVP_CIPH_NO_PADDING ; 
 int /*<<< orphan*/  EVP_F_EVP_ENCRYPTFINAL_EX ; 
 int /*<<< orphan*/  EVP_R_DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int stub1 (TYPE_2__*,unsigned char*,int*,unsigned int) ; 
 int stub2 (TYPE_2__*,unsigned char*,int*,unsigned int) ; 

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl)
{
    int n, ret;
    unsigned int i, b, bl;

    /* Prevent accidental use of decryption context when encrypting */
    if (!ctx->encrypt) {
        EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX, EVP_R_INVALID_OPERATION);
        return 0;
    }

    if (ctx->cipher->flags & EVP_CIPH_FLAG_CUSTOM_CIPHER) {
        ret = ctx->cipher->do_cipher(ctx, out, NULL, 0);
        if (ret < 0)
            return 0;
        else
            *outl = ret;
        return 1;
    }

    b = ctx->cipher->block_size;
    OPENSSL_assert(b <= sizeof(ctx->buf));
    if (b == 1) {
        *outl = 0;
        return 1;
    }
    bl = ctx->buf_len;
    if (ctx->flags & EVP_CIPH_NO_PADDING) {
        if (bl) {
            EVPerr(EVP_F_EVP_ENCRYPTFINAL_EX,
                   EVP_R_DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH);
            return 0;
        }
        *outl = 0;
        return 1;
    }

    n = b - bl;
    for (i = bl; i < b; i++)
        ctx->buf[i] = n;
    ret = ctx->cipher->do_cipher(ctx, out, ctx->buf, b);

    if (ret)
        *outl = b;

    return ret;
}