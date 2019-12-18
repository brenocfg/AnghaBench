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
struct TYPE_4__ {void** d; } ;
struct TYPE_5__ {scalar_t__ partial_len; void** counter; TYPE_1__ key; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  TYPE_2__ EVP_CHACHA_KEY ;

/* Variables and functions */
 unsigned int CHACHA_CTR_SIZE ; 
 unsigned int CHACHA_KEY_SIZE ; 
 void* CHACHA_U8TOU32 (unsigned char const*) ; 
 TYPE_2__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chacha_init_key(EVP_CIPHER_CTX *ctx,
                           const unsigned char user_key[CHACHA_KEY_SIZE],
                           const unsigned char iv[CHACHA_CTR_SIZE], int enc)
{
    EVP_CHACHA_KEY *key = data(ctx);
    unsigned int i;

    if (user_key)
        for (i = 0; i < CHACHA_KEY_SIZE; i+=4) {
            key->key.d[i/4] = CHACHA_U8TOU32(user_key+i);
        }

    if (iv)
        for (i = 0; i < CHACHA_CTR_SIZE; i+=4) {
            key->counter[i/4] = CHACHA_U8TOU32(iv+i);
        }

    key->partial_len = 0;

    return 1;
}