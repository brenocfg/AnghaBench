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
struct TYPE_4__ {int nid; int block_size; int key_len; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_CIPHER *EVP_CIPHER_meth_new(int cipher_type, int block_size, int key_len)
{
    EVP_CIPHER *cipher = OPENSSL_zalloc(sizeof(EVP_CIPHER));

    if (cipher != NULL) {
        cipher->nid = cipher_type;
        cipher->block_size = block_size;
        cipher->key_len = key_len;
    }
    return cipher;
}