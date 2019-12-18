#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int OPENSSL_ppccap_P ; 
 int PPC_CRYPTO207 ; 
 int /*<<< orphan*/  sha512_block_p8 (void*,void const*,size_t) ; 
 int /*<<< orphan*/  sha512_block_ppc (void*,void const*,size_t) ; 

void sha512_block_data_order(void *ctx, const void *inp, size_t len)
{
    OPENSSL_ppccap_P & PPC_CRYPTO207 ? sha512_block_p8(ctx, inp, len) :
        sha512_block_ppc(ctx, inp, len);
}