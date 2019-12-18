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
typedef  int /*<<< orphan*/  crypto_generichash_state ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_box_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_generichash_final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_generichash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_generichash_update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_crypto_box_seal_nonce(unsigned char *nonce,
                       const unsigned char *pk1, const unsigned char *pk2)
{
    crypto_generichash_state st;

    crypto_generichash_init(&st, NULL, 0U, crypto_box_NONCEBYTES);
    crypto_generichash_update(&st, pk1, crypto_box_PUBLICKEYBYTES);
    crypto_generichash_update(&st, pk2, crypto_box_PUBLICKEYBYTES);
    crypto_generichash_final(&st, nonce, crypto_box_NONCEBYTES);

    return 0;
}