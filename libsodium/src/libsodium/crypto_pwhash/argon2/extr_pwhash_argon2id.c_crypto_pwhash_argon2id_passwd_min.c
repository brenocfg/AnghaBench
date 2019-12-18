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
 scalar_t__ ARGON2_MIN_PWD_LENGTH ; 
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 scalar_t__ crypto_pwhash_argon2id_PASSWD_MIN ; 

size_t
crypto_pwhash_argon2id_passwd_min(void)
{
    COMPILER_ASSERT(crypto_pwhash_argon2id_PASSWD_MIN >= ARGON2_MIN_PWD_LENGTH);
    return crypto_pwhash_argon2id_PASSWD_MIN;
}