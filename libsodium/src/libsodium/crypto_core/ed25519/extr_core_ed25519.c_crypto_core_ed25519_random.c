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
 int crypto_core_ed25519_HASHBYTES ; 
 int /*<<< orphan*/  crypto_core_ed25519_from_hash (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,int) ; 

void
crypto_core_ed25519_random(unsigned char *p)
{
    unsigned char h[crypto_core_ed25519_HASHBYTES];

    randombytes_buf(h, sizeof h);
    (void) crypto_core_ed25519_from_hash(p, h);
}