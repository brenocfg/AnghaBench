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
 int crypto_core_ed25519_NONREDUCEDSCALARBYTES ; 
 int crypto_core_ed25519_SCALARBYTES ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

void
crypto_core_ed25519_scalar_reduce(unsigned char *r,
                                  const unsigned char *s)
{
    unsigned char t[crypto_core_ed25519_NONREDUCEDSCALARBYTES];

    memcpy(t, s, sizeof t);
    sc25519_reduce(t);
    memcpy(r, t, crypto_core_ed25519_SCALARBYTES);
    sodium_memzero(t, sizeof t);
}