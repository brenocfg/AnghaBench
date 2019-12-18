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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  escrypt_local_t ;

/* Variables and functions */
 int crypto_pwhash_scryptsalsa208sha256_STRBYTES ; 
 int /*<<< orphan*/  escrypt_free_local (int /*<<< orphan*/ *) ; 
 scalar_t__ escrypt_init_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * escrypt_r (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int sodium_memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  sodium_memzero (char*,int) ; 
 int sodium_strnlen (char const*,int) ; 

int
crypto_pwhash_scryptsalsa208sha256_str_verify(
    const char        str[crypto_pwhash_scryptsalsa208sha256_STRBYTES],
    const char *const passwd, unsigned long long passwdlen)
{
    char            wanted[crypto_pwhash_scryptsalsa208sha256_STRBYTES];
    escrypt_local_t escrypt_local;
    int             ret = -1;

    if (sodium_strnlen(str, crypto_pwhash_scryptsalsa208sha256_STRBYTES) !=
        crypto_pwhash_scryptsalsa208sha256_STRBYTES - 1U) {
        return -1;
    }
    if (escrypt_init_local(&escrypt_local) != 0) {
        return -1; /* LCOV_EXCL_LINE */
    }
    memset(wanted, 0, sizeof wanted);
    if (escrypt_r(&escrypt_local, (const uint8_t *) passwd, (size_t) passwdlen,
                  (const uint8_t *) str, (uint8_t *) wanted,
                  sizeof wanted) == NULL) {
        escrypt_free_local(&escrypt_local);
        return -1;
    }
    escrypt_free_local(&escrypt_local);
    ret = sodium_memcmp(wanted, str, sizeof wanted);
    sodium_memzero(wanted, sizeof wanted);

    return ret;
}