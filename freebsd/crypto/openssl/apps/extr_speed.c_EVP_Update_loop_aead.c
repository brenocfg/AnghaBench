#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* buf; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  faketag ;
typedef  int /*<<< orphan*/  aad ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ COND (int) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 int /*<<< orphan*/  EVP_DecryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DecryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int) ; 
 scalar_t__ decrypt ; 
 int /*<<< orphan*/  iv ; 
 int* lengths ; 
 int save_count ; 
 size_t testnum ; 

__attribute__((used)) static int EVP_Update_loop_aead(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    EVP_CIPHER_CTX *ctx = tempargs->ctx;
    int outl, count;
    unsigned char aad[13] = { 0xcc };
    unsigned char faketag[16] = { 0xcc };
#ifndef SIGALRM
    int nb_iter = save_count * 4 * lengths[0] / lengths[testnum];
#endif
    if (decrypt) {
        for (count = 0; COND(nb_iter); count++) {
            EVP_DecryptInit_ex(ctx, NULL, NULL, NULL, iv);
            EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG,
                                sizeof(faketag), faketag);
            EVP_DecryptUpdate(ctx, NULL, &outl, aad, sizeof(aad));
            EVP_DecryptUpdate(ctx, buf, &outl, buf, lengths[testnum]);
            EVP_DecryptFinal_ex(ctx, buf + outl, &outl);
        }
    } else {
        for (count = 0; COND(nb_iter); count++) {
            EVP_EncryptInit_ex(ctx, NULL, NULL, NULL, iv);
            EVP_EncryptUpdate(ctx, NULL, &outl, aad, sizeof(aad));
            EVP_EncryptUpdate(ctx, buf, &outl, buf, lengths[testnum]);
            EVP_EncryptFinal_ex(ctx, buf + outl, &outl);
        }
    }
    return count;
}