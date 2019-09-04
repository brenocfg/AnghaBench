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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_pwhash_argon2i_ALG_ARGON2I13 ; 
 unsigned int crypto_pwhash_argon2i_BYTES_MAX ; 
 unsigned int crypto_pwhash_argon2i_BYTES_MIN ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_INTERACTIVE ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_MAX ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_MIN ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_MODERATE ; 
 unsigned int crypto_pwhash_argon2i_MEMLIMIT_SENSITIVE ; 
 unsigned int crypto_pwhash_argon2i_OPSLIMIT_INTERACTIVE ; 
 unsigned int crypto_pwhash_argon2i_OPSLIMIT_MAX ; 
 unsigned int crypto_pwhash_argon2i_OPSLIMIT_MIN ; 
 unsigned int crypto_pwhash_argon2i_OPSLIMIT_MODERATE ; 
 unsigned int crypto_pwhash_argon2i_OPSLIMIT_SENSITIVE ; 
 scalar_t__ crypto_pwhash_argon2i_PASSWD_MAX ; 
 scalar_t__ crypto_pwhash_argon2i_PASSWD_MIN ; 
 unsigned int crypto_pwhash_argon2i_SALTBYTES ; 
 unsigned int crypto_pwhash_argon2i_STRBYTES ; 
 scalar_t__ crypto_pwhash_argon2i_alg_argon2i13 () ; 
 unsigned int crypto_pwhash_argon2i_bytes_max () ; 
 unsigned int crypto_pwhash_argon2i_bytes_min () ; 
 unsigned int crypto_pwhash_argon2i_memlimit_interactive () ; 
 unsigned int crypto_pwhash_argon2i_memlimit_max () ; 
 unsigned int crypto_pwhash_argon2i_memlimit_min () ; 
 unsigned int crypto_pwhash_argon2i_memlimit_moderate () ; 
 unsigned int crypto_pwhash_argon2i_memlimit_sensitive () ; 
 unsigned int crypto_pwhash_argon2i_opslimit_interactive () ; 
 unsigned int crypto_pwhash_argon2i_opslimit_max () ; 
 unsigned int crypto_pwhash_argon2i_opslimit_min () ; 
 unsigned int crypto_pwhash_argon2i_opslimit_moderate () ; 
 unsigned int crypto_pwhash_argon2i_opslimit_sensitive () ; 
 scalar_t__ crypto_pwhash_argon2i_passwd_max () ; 
 scalar_t__ crypto_pwhash_argon2i_passwd_min () ; 
 unsigned int crypto_pwhash_argon2i_saltbytes () ; 
 unsigned int crypto_pwhash_argon2i_strbytes () ; 
 int /*<<< orphan*/  crypto_pwhash_argon2i_strprefix () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  str_tests () ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv () ; 
 int /*<<< orphan*/  tv2 () ; 
 int /*<<< orphan*/  tv3 () ; 

int
main(void)
{
    tv();
    tv2();
    tv3();
    str_tests();

    assert(crypto_pwhash_argon2i_bytes_min() > 0U);
    assert(crypto_pwhash_argon2i_bytes_max() > crypto_pwhash_argon2i_bytes_min());
    assert(crypto_pwhash_argon2i_passwd_max() > crypto_pwhash_argon2i_passwd_min());
    assert(crypto_pwhash_argon2i_saltbytes() > 0U);
    assert(crypto_pwhash_argon2i_strbytes() > 1U);
    assert(crypto_pwhash_argon2i_strbytes() > strlen(crypto_pwhash_argon2i_strprefix()));

    assert(crypto_pwhash_argon2i_opslimit_min() > 0U);
    assert(crypto_pwhash_argon2i_opslimit_max() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_min() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_max() > 0U);
    assert(crypto_pwhash_argon2i_opslimit_interactive() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_interactive() > 0U);
    assert(crypto_pwhash_argon2i_opslimit_moderate() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_moderate() > 0U);
    assert(crypto_pwhash_argon2i_opslimit_sensitive() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_sensitive() > 0U);

    assert(crypto_pwhash_argon2i_bytes_min() == crypto_pwhash_argon2i_BYTES_MIN);
    assert(crypto_pwhash_argon2i_bytes_max() == crypto_pwhash_argon2i_BYTES_MAX);
    assert(crypto_pwhash_argon2i_passwd_min() == crypto_pwhash_argon2i_PASSWD_MIN);
    assert(crypto_pwhash_argon2i_passwd_max() == crypto_pwhash_argon2i_PASSWD_MAX);
    assert(crypto_pwhash_argon2i_saltbytes() == crypto_pwhash_argon2i_SALTBYTES);
    assert(crypto_pwhash_argon2i_strbytes() == crypto_pwhash_argon2i_STRBYTES);

    assert(crypto_pwhash_argon2i_opslimit_min() == crypto_pwhash_argon2i_OPSLIMIT_MIN);
    assert(crypto_pwhash_argon2i_opslimit_max() == crypto_pwhash_argon2i_OPSLIMIT_MAX);
    assert(crypto_pwhash_argon2i_memlimit_min() == crypto_pwhash_argon2i_MEMLIMIT_MIN);
    assert(crypto_pwhash_argon2i_memlimit_max() == crypto_pwhash_argon2i_MEMLIMIT_MAX);
    assert(crypto_pwhash_argon2i_opslimit_interactive() ==
           crypto_pwhash_argon2i_OPSLIMIT_INTERACTIVE);
    assert(crypto_pwhash_argon2i_memlimit_interactive() ==
           crypto_pwhash_argon2i_MEMLIMIT_INTERACTIVE);
    assert(crypto_pwhash_argon2i_opslimit_moderate() ==
           crypto_pwhash_argon2i_OPSLIMIT_MODERATE);
    assert(crypto_pwhash_argon2i_memlimit_moderate() ==
           crypto_pwhash_argon2i_MEMLIMIT_MODERATE);
    assert(crypto_pwhash_argon2i_opslimit_sensitive() ==
           crypto_pwhash_argon2i_OPSLIMIT_SENSITIVE);
    assert(crypto_pwhash_argon2i_memlimit_sensitive() ==
           crypto_pwhash_argon2i_MEMLIMIT_SENSITIVE);

    assert(crypto_pwhash_argon2i_alg_argon2i13() == crypto_pwhash_argon2i_ALG_ARGON2I13);

    printf("OK\n");

    return 0;
}