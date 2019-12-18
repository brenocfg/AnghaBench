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
struct TYPE_6__ {TYPE_1__* cipher; } ;
struct TYPE_5__ {int (* do_cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ;} ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int stub1 (TYPE_2__*,unsigned char*,unsigned char const*,unsigned int) ; 

int EVP_Cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
               const unsigned char *in, unsigned int inl)
{
    return ctx->cipher->do_cipher(ctx, out, in, inl);
}