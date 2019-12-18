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
 scalar_t__ crypto_pwhash_ALG_ARGON2I13 ; 
 scalar_t__ crypto_pwhash_ALG_ARGON2ID13 ; 
 unsigned int crypto_pwhash_BYTES_MAX ; 
 unsigned int crypto_pwhash_BYTES_MIN ; 
 unsigned int crypto_pwhash_MEMLIMIT_INTERACTIVE ; 
 unsigned int crypto_pwhash_MEMLIMIT_MAX ; 
 unsigned int crypto_pwhash_MEMLIMIT_MIN ; 
 unsigned int crypto_pwhash_MEMLIMIT_MODERATE ; 
 unsigned int crypto_pwhash_MEMLIMIT_SENSITIVE ; 
 unsigned int crypto_pwhash_OPSLIMIT_INTERACTIVE ; 
 unsigned int crypto_pwhash_OPSLIMIT_MAX ; 
 unsigned int crypto_pwhash_OPSLIMIT_MIN ; 
 unsigned int crypto_pwhash_OPSLIMIT_MODERATE ; 
 unsigned int crypto_pwhash_OPSLIMIT_SENSITIVE ; 
 scalar_t__ crypto_pwhash_PASSWD_MAX ; 
 scalar_t__ crypto_pwhash_PASSWD_MIN ; 
 unsigned int crypto_pwhash_SALTBYTES ; 
 unsigned int crypto_pwhash_STRBYTES ; 
 scalar_t__ crypto_pwhash_alg_argon2i13 () ; 
 scalar_t__ crypto_pwhash_alg_argon2id13 () ; 
 scalar_t__ crypto_pwhash_alg_default () ; 
 int crypto_pwhash_argon2i (scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int crypto_pwhash_argon2id (scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE ; 
 int /*<<< orphan*/  crypto_pwhash_argon2id_OPSLIMIT_INTERACTIVE ; 
 scalar_t__ crypto_pwhash_argon2id_alg_argon2id13 () ; 
 unsigned int crypto_pwhash_argon2id_bytes_max () ; 
 unsigned int crypto_pwhash_argon2id_bytes_min () ; 
 unsigned int crypto_pwhash_argon2id_memlimit_interactive () ; 
 unsigned int crypto_pwhash_argon2id_memlimit_max () ; 
 unsigned int crypto_pwhash_argon2id_memlimit_min () ; 
 unsigned int crypto_pwhash_argon2id_memlimit_moderate () ; 
 unsigned int crypto_pwhash_argon2id_memlimit_sensitive () ; 
 unsigned int crypto_pwhash_argon2id_opslimit_interactive () ; 
 unsigned int crypto_pwhash_argon2id_opslimit_max () ; 
 unsigned int crypto_pwhash_argon2id_opslimit_min () ; 
 unsigned int crypto_pwhash_argon2id_opslimit_moderate () ; 
 unsigned int crypto_pwhash_argon2id_opslimit_sensitive () ; 
 scalar_t__ crypto_pwhash_argon2id_passwd_max () ; 
 scalar_t__ crypto_pwhash_argon2id_passwd_min () ; 
 unsigned int crypto_pwhash_argon2id_saltbytes () ; 
 unsigned int crypto_pwhash_argon2id_strbytes () ; 
 int /*<<< orphan*/  crypto_pwhash_argon2id_strprefix () ; 
 unsigned int crypto_pwhash_bytes_max () ; 
 unsigned int crypto_pwhash_bytes_min () ; 
 unsigned int crypto_pwhash_memlimit_interactive () ; 
 unsigned int crypto_pwhash_memlimit_max () ; 
 unsigned int crypto_pwhash_memlimit_min () ; 
 unsigned int crypto_pwhash_memlimit_moderate () ; 
 unsigned int crypto_pwhash_memlimit_sensitive () ; 
 unsigned int crypto_pwhash_opslimit_interactive () ; 
 unsigned int crypto_pwhash_opslimit_max () ; 
 unsigned int crypto_pwhash_opslimit_min () ; 
 unsigned int crypto_pwhash_opslimit_moderate () ; 
 unsigned int crypto_pwhash_opslimit_sensitive () ; 
 scalar_t__ crypto_pwhash_passwd_max () ; 
 scalar_t__ crypto_pwhash_passwd_min () ; 
 int /*<<< orphan*/  crypto_pwhash_primitive () ; 
 unsigned int crypto_pwhash_saltbytes () ; 
 unsigned int crypto_pwhash_strbytes () ; 
 char* crypto_pwhash_strprefix () ; 
 scalar_t__ guard_page ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  str_tests () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 unsigned int strlen (char*) ; 
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

    assert(crypto_pwhash_bytes_min() > 0U);
    assert(crypto_pwhash_bytes_max() > crypto_pwhash_bytes_min());
    assert(crypto_pwhash_passwd_max() > crypto_pwhash_passwd_min());
    assert(crypto_pwhash_saltbytes() > 0U);
    assert(crypto_pwhash_strbytes() > 1U);
    assert(crypto_pwhash_strbytes() > strlen(crypto_pwhash_strprefix()));

    assert(crypto_pwhash_opslimit_min() > 0U);
    assert(crypto_pwhash_opslimit_max() > 0U);
    assert(crypto_pwhash_memlimit_min() > 0U);
    assert(crypto_pwhash_memlimit_max() > 0U);
    assert(crypto_pwhash_opslimit_interactive() > 0U);
    assert(crypto_pwhash_memlimit_interactive() > 0U);
    assert(crypto_pwhash_opslimit_moderate() > 0U);
    assert(crypto_pwhash_memlimit_moderate() > 0U);
    assert(crypto_pwhash_opslimit_sensitive() > 0U);
    assert(crypto_pwhash_memlimit_sensitive() > 0U);
    assert(strcmp(crypto_pwhash_primitive(), "argon2i") == 0);

    assert(crypto_pwhash_bytes_min() == crypto_pwhash_BYTES_MIN);
    assert(crypto_pwhash_bytes_max() == crypto_pwhash_BYTES_MAX);
    assert(crypto_pwhash_passwd_min() == crypto_pwhash_PASSWD_MIN);
    assert(crypto_pwhash_passwd_max() == crypto_pwhash_PASSWD_MAX);
    assert(crypto_pwhash_saltbytes() == crypto_pwhash_SALTBYTES);
    assert(crypto_pwhash_strbytes() == crypto_pwhash_STRBYTES);

    assert(crypto_pwhash_opslimit_min() == crypto_pwhash_OPSLIMIT_MIN);
    assert(crypto_pwhash_opslimit_max() == crypto_pwhash_OPSLIMIT_MAX);
    assert(crypto_pwhash_memlimit_min() == crypto_pwhash_MEMLIMIT_MIN);
    assert(crypto_pwhash_memlimit_max() == crypto_pwhash_MEMLIMIT_MAX);
    assert(crypto_pwhash_opslimit_interactive() ==
           crypto_pwhash_OPSLIMIT_INTERACTIVE);
    assert(crypto_pwhash_memlimit_interactive() ==
           crypto_pwhash_MEMLIMIT_INTERACTIVE);
    assert(crypto_pwhash_opslimit_moderate() ==
           crypto_pwhash_OPSLIMIT_MODERATE);
    assert(crypto_pwhash_memlimit_moderate() ==
           crypto_pwhash_MEMLIMIT_MODERATE);
    assert(crypto_pwhash_opslimit_sensitive() ==
           crypto_pwhash_OPSLIMIT_SENSITIVE);
    assert(crypto_pwhash_memlimit_sensitive() ==
           crypto_pwhash_MEMLIMIT_SENSITIVE);

    assert(crypto_pwhash_argon2id_bytes_min() == crypto_pwhash_bytes_min());
    assert(crypto_pwhash_argon2id_bytes_max() == crypto_pwhash_bytes_max());
    assert(crypto_pwhash_argon2id_passwd_min() == crypto_pwhash_passwd_min());
    assert(crypto_pwhash_argon2id_passwd_max() == crypto_pwhash_passwd_max());
    assert(crypto_pwhash_argon2id_saltbytes() == crypto_pwhash_saltbytes());
    assert(crypto_pwhash_argon2id_strbytes() == crypto_pwhash_strbytes());
    assert(strcmp(crypto_pwhash_argon2id_strprefix(),
                  crypto_pwhash_strprefix()) == 0);
    assert(crypto_pwhash_argon2id_opslimit_min() ==
           crypto_pwhash_opslimit_min());
    assert(crypto_pwhash_argon2id_opslimit_max() ==
           crypto_pwhash_opslimit_max());
    assert(crypto_pwhash_argon2id_memlimit_min() ==
           crypto_pwhash_memlimit_min());
    assert(crypto_pwhash_argon2id_memlimit_max() ==
           crypto_pwhash_memlimit_max());
    assert(crypto_pwhash_argon2id_opslimit_interactive() ==
           crypto_pwhash_opslimit_interactive());
    assert(crypto_pwhash_argon2id_opslimit_moderate() ==
           crypto_pwhash_opslimit_moderate());
    assert(crypto_pwhash_argon2id_opslimit_sensitive() ==
           crypto_pwhash_opslimit_sensitive());
    assert(crypto_pwhash_argon2id_memlimit_interactive() ==
           crypto_pwhash_memlimit_interactive());
    assert(crypto_pwhash_argon2id_memlimit_moderate() ==
           crypto_pwhash_memlimit_moderate());
    assert(crypto_pwhash_argon2id_memlimit_sensitive() ==
           crypto_pwhash_memlimit_sensitive());
    assert(crypto_pwhash_alg_argon2id13() ==
           crypto_pwhash_argon2id_alg_argon2id13());
    assert(crypto_pwhash_alg_argon2i13() == crypto_pwhash_ALG_ARGON2I13);
    assert(crypto_pwhash_alg_argon2i13() != crypto_pwhash_alg_default());
    assert(crypto_pwhash_alg_argon2id13() == crypto_pwhash_ALG_ARGON2ID13);
    assert(crypto_pwhash_alg_argon2id13() != crypto_pwhash_alg_argon2i13());
    assert(crypto_pwhash_alg_argon2id13() == crypto_pwhash_alg_default());

    assert(crypto_pwhash_argon2id(guard_page, 0, (const char *) guard_page, 0, guard_page,
                                  crypto_pwhash_argon2id_OPSLIMIT_INTERACTIVE,
                                  crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE,
                                  0) == -1);
    assert(crypto_pwhash_argon2id(guard_page, 0, (const char *) guard_page, 0, guard_page,
                                 crypto_pwhash_argon2id_OPSLIMIT_INTERACTIVE,
                                 crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE,
                                 crypto_pwhash_ALG_ARGON2I13) == -1);
    assert(crypto_pwhash_argon2i(guard_page, 0, (const char *) guard_page, 0, guard_page,
                                 crypto_pwhash_argon2id_OPSLIMIT_INTERACTIVE,
                                 crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE,
                                 0) == -1);
    assert(crypto_pwhash_argon2i(guard_page, 0, (const char *) guard_page, 0, guard_page,
                                 crypto_pwhash_argon2id_OPSLIMIT_INTERACTIVE,
                                 crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE,
                                 crypto_pwhash_ALG_ARGON2ID13) == -1);

    printf("OK\n");

    return 0;
}