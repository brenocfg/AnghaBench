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
 unsigned int ARGON2_MIN_MEMORY ; 
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_MIN ; 

size_t
crypto_pwhash_argon2i_memlimit_min(void)
{
    COMPILER_ASSERT((crypto_pwhash_argon2i_MEMLIMIT_MIN / 1024U) >= ARGON2_MIN_MEMORY);
    return crypto_pwhash_argon2i_MEMLIMIT_MIN;
}