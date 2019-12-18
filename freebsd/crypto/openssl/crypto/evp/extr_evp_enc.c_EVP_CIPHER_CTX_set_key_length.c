#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int key_len; TYPE_1__* cipher; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int EVP_CIPH_CUSTOM_KEY_LENGTH ; 
 int EVP_CIPH_VARIABLE_LENGTH ; 
 int /*<<< orphan*/  EVP_CTRL_SET_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_CTX_SET_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX *c, int keylen)
{
    if (c->cipher->flags & EVP_CIPH_CUSTOM_KEY_LENGTH)
        return EVP_CIPHER_CTX_ctrl(c, EVP_CTRL_SET_KEY_LENGTH, keylen, NULL);
    if (c->key_len == keylen)
        return 1;
    if ((keylen > 0) && (c->cipher->flags & EVP_CIPH_VARIABLE_LENGTH)) {
        c->key_len = keylen;
        return 1;
    }
    EVPerr(EVP_F_EVP_CIPHER_CTX_SET_KEY_LENGTH, EVP_R_INVALID_KEY_LENGTH);
    return 0;
}