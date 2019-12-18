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
struct TYPE_7__ {int /*<<< orphan*/  engine; scalar_t__ cipher_data; TYPE_1__* cipher; } ;
struct TYPE_6__ {scalar_t__ ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OPENSSL_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX *c)
{
    if (c == NULL)
        return 1;
    if (c->cipher != NULL) {
        if (c->cipher->cleanup && !c->cipher->cleanup(c))
            return 0;
        /* Cleanse cipher context data */
        if (c->cipher_data && c->cipher->ctx_size)
            OPENSSL_cleanse(c->cipher_data, c->cipher->ctx_size);
    }
    OPENSSL_free(c->cipher_data);
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(c->engine);
#endif
    memset(c, 0, sizeof(*c));
    return 1;
}