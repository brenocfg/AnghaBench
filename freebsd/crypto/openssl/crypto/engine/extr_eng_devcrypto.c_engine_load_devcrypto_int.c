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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_new () ; 
 int /*<<< orphan*/  ENGINE_set_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_EC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_ciphers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_destroy_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_digests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cfd ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devcrypto_ciphers ; 
 int /*<<< orphan*/  devcrypto_dh ; 
 int /*<<< orphan*/  devcrypto_digests ; 
 int /*<<< orphan*/  devcrypto_dsa ; 
 int /*<<< orphan*/  devcrypto_ec ; 
 int /*<<< orphan*/  devcrypto_rsa ; 
 int /*<<< orphan*/  devcrypto_unload ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_cipher_methods () ; 
 int /*<<< orphan*/  prepare_digest_methods () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

void engine_load_devcrypto_int()
{
    ENGINE *e = NULL;

    if ((cfd = open("/dev/crypto", O_RDWR, 0)) < 0) {
#ifndef ENGINE_DEVCRYPTO_DEBUG
        if (errno != ENOENT)
#endif
            fprintf(stderr, "Could not open /dev/crypto: %s\n", strerror(errno));
        return;
    }

    if ((e = ENGINE_new()) == NULL
        || !ENGINE_set_destroy_function(e, devcrypto_unload)) {
        ENGINE_free(e);
        /*
         * We know that devcrypto_unload() won't be called when one of the
         * above two calls have failed, so we close cfd explicitly here to
         * avoid leaking resources.
         */
        close(cfd);
        return;
    }

    prepare_cipher_methods();
#ifdef IMPLEMENT_DIGEST
    prepare_digest_methods();
#endif

    if (!ENGINE_set_id(e, "devcrypto")
        || !ENGINE_set_name(e, "/dev/crypto engine")

/*
 * Asymmetric ciphers aren't well supported with /dev/crypto.  Among the BSD
 * implementations, it seems to only exist in FreeBSD, and regarding the
 * parameters in its crypt_kop, the manual crypto(4) has this to say:
 *
 *    The semantics of these arguments are currently undocumented.
 *
 * Reading through the FreeBSD source code doesn't give much more than
 * their CRK_MOD_EXP implementation for ubsec.
 *
 * It doesn't look much better with cryptodev-linux.  They have the crypt_kop
 * structure as well as the command (CRK_*) in cryptodev.h, but no support
 * seems to be implemented at all for the moment.
 *
 * At the time of writing, it seems impossible to write proper support for
 * FreeBSD's asym features without some very deep knowledge and access to
 * specific kernel modules.
 *
 * /Richard Levitte, 2017-05-11
 */
#if 0
# ifndef OPENSSL_NO_RSA
        || !ENGINE_set_RSA(e, devcrypto_rsa)
# endif
# ifndef OPENSSL_NO_DSA
        || !ENGINE_set_DSA(e, devcrypto_dsa)
# endif
# ifndef OPENSSL_NO_DH
        || !ENGINE_set_DH(e, devcrypto_dh)
# endif
# ifndef OPENSSL_NO_EC
        || !ENGINE_set_EC(e, devcrypto_ec)
# endif
#endif
        || !ENGINE_set_ciphers(e, devcrypto_ciphers)
#ifdef IMPLEMENT_DIGEST
        || !ENGINE_set_digests(e, devcrypto_digests)
#endif
        ) {
        ENGINE_free(e);
        return;
    }

    ENGINE_add(e);
    ENGINE_free(e);          /* Loose our local reference */
    ERR_clear_error();
}