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
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 unsigned char* L ; 
 int crypto_core_ed25519_NONREDUCEDSCALARBYTES ; 
 int crypto_core_ed25519_SCALARBYTES ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 
 int /*<<< orphan*/  sodium_sub (unsigned char*,unsigned char*,int) ; 

void
crypto_core_ed25519_scalar_negate(unsigned char *neg, const unsigned char *s)
{
    unsigned char t_[crypto_core_ed25519_NONREDUCEDSCALARBYTES];
    unsigned char s_[crypto_core_ed25519_NONREDUCEDSCALARBYTES];

    COMPILER_ASSERT(crypto_core_ed25519_NONREDUCEDSCALARBYTES >=
                    2 * crypto_core_ed25519_SCALARBYTES);
    memset(t_, 0, sizeof t_);
    memset(s_, 0, sizeof s_);
    memcpy(t_ + crypto_core_ed25519_SCALARBYTES, L,
           crypto_core_ed25519_SCALARBYTES);
    memcpy(s_, s, crypto_core_ed25519_SCALARBYTES);
    sodium_sub(t_, s_, sizeof t_);
    sc25519_reduce(t_);
    memcpy(neg, t_, crypto_core_ed25519_SCALARBYTES);
}