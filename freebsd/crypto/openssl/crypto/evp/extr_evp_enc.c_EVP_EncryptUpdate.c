#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  encrypt; } ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_ENCRYPTUPDATE ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evp_EncryptDecryptUpdate (TYPE_1__*,unsigned char*,int*,unsigned char const*,int) ; 

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl,
                      const unsigned char *in, int inl)
{
    /* Prevent accidental use of decryption context when encrypting */
    if (!ctx->encrypt) {
        EVPerr(EVP_F_EVP_ENCRYPTUPDATE, EVP_R_INVALID_OPERATION);
        return 0;
    }

    return evp_EncryptDecryptUpdate(ctx, out, outl, in, inl);
}