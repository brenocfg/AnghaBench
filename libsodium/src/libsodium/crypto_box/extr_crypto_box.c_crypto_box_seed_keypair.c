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
 int crypto_box_curve25519xsalsa20poly1305_seed_keypair (unsigned char*,unsigned char*,unsigned char const*) ; 

int
crypto_box_seed_keypair(unsigned char *pk, unsigned char *sk,
                        const unsigned char *seed)
{
    return crypto_box_curve25519xsalsa20poly1305_seed_keypair(pk, sk, seed);
}