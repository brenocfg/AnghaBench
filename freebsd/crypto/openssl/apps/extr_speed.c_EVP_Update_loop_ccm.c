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
typedef  int /*<<< orphan*/  tag ;
struct TYPE_2__ {unsigned char* buf; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ COND (int) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 int /*<<< orphan*/  EVP_DecryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DecryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int) ; 
 scalar_t__ decrypt ; 
 int /*<<< orphan*/  iv ; 
 int* lengths ; 
 int save_count ; 
 size_t testnum ; 

__attribute__((used)) static int EVP_Update_loop_ccm(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    EVP_CIPHER_CTX *ctx = tempargs->ctx;
    int outl, count;
    unsigned char tag[12];
#ifndef SIGALRM
    int nb_iter = save_count * 4 * lengths[0] / lengths[testnum];
#endif
    if (decrypt) {
        for (count = 0; COND(nb_iter); count++) {
            EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, sizeof(tag), tag);
            /* reset iv */
            EVP_DecryptInit_ex(ctx, NULL, NULL, NULL, iv);
            /* counter is reset on every update */
            EVP_DecryptUpdate(ctx, buf, &outl, buf, lengths[testnum]);
        }
    } else {
        for (count = 0; COND(nb_iter); count++) {
            /* restore iv length field */
            EVP_EncryptUpdate(ctx, NULL, &outl, NULL, lengths[testnum]);
            /* counter is reset on every update */
            EVP_EncryptUpdate(ctx, buf, &outl, buf, lengths[testnum]);
        }
    }
    if (decrypt)
        EVP_DecryptFinal_ex(ctx, buf, &outl);
    else
        EVP_EncryptFinal_ex(ctx, buf, &outl);
    return count;
}