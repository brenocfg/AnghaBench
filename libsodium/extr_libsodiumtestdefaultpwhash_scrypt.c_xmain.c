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
 unsigned int crypto_pwhash_scryptsalsa208sha256_bytes_max () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_bytes_min () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_memlimit_interactive () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_memlimit_max () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_memlimit_min () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_memlimit_sensitive () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_opslimit_interactive () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_opslimit_max () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_opslimit_min () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_opslimit_sensitive () ; 
 scalar_t__ crypto_pwhash_scryptsalsa208sha256_passwd_max () ; 
 scalar_t__ crypto_pwhash_scryptsalsa208sha256_passwd_min () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_saltbytes () ; 
 unsigned int crypto_pwhash_scryptsalsa208sha256_strbytes () ; 
 int /*<<< orphan*/  crypto_pwhash_scryptsalsa208sha256_strprefix () ; 
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

    assert(crypto_pwhash_scryptsalsa208sha256_bytes_min() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_bytes_max() >
           crypto_pwhash_scryptsalsa208sha256_bytes_min());
    assert(crypto_pwhash_scryptsalsa208sha256_passwd_max() >
           crypto_pwhash_scryptsalsa208sha256_passwd_min());
    assert(crypto_pwhash_scryptsalsa208sha256_saltbytes() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_strbytes() > 1U);
    assert(crypto_pwhash_scryptsalsa208sha256_strbytes() >
           strlen(crypto_pwhash_scryptsalsa208sha256_strprefix()));

    assert(crypto_pwhash_scryptsalsa208sha256_opslimit_min() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_opslimit_max() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_memlimit_min() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_memlimit_max() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_opslimit_interactive() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_memlimit_interactive() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_opslimit_sensitive() > 0U);
    assert(crypto_pwhash_scryptsalsa208sha256_memlimit_sensitive() > 0U);

    printf("OK\n");

    return 0;
}