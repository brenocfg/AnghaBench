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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ARGON2_OK ; 
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  STR_HASHBYTES ; 
 scalar_t__ argon2i_hash_encoded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,size_t,unsigned char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t crypto_pwhash_argon2i_MEMLIMIT_MAX ; 
 size_t crypto_pwhash_argon2i_MEMLIMIT_MIN ; 
 unsigned long long crypto_pwhash_argon2i_OPSLIMIT_MAX ; 
 unsigned long long crypto_pwhash_argon2i_OPSLIMIT_MIN ; 
 unsigned long long crypto_pwhash_argon2i_PASSWD_MAX ; 
 unsigned long long crypto_pwhash_argon2i_PASSWD_MIN ; 
 int crypto_pwhash_argon2i_SALTBYTES ; 
 int /*<<< orphan*/  crypto_pwhash_argon2i_STRBYTES ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,int) ; 

int
crypto_pwhash_argon2i_str(char out[crypto_pwhash_argon2i_STRBYTES],
                          const char *const passwd,
                          unsigned long long passwdlen,
                          unsigned long long opslimit, size_t memlimit)
{
    unsigned char salt[crypto_pwhash_argon2i_SALTBYTES];

    memset(out, 0, crypto_pwhash_argon2i_STRBYTES);
    if (passwdlen > crypto_pwhash_argon2i_PASSWD_MAX ||
        opslimit > crypto_pwhash_argon2i_OPSLIMIT_MAX ||
        memlimit > crypto_pwhash_argon2i_MEMLIMIT_MAX) {
        errno = EFBIG;
        return -1;
    }
    if (passwdlen < crypto_pwhash_argon2i_PASSWD_MIN ||
        opslimit < crypto_pwhash_argon2i_OPSLIMIT_MIN ||
        memlimit < crypto_pwhash_argon2i_MEMLIMIT_MIN) {
        errno = EINVAL;
        return -1;
    }
    randombytes_buf(salt, sizeof salt);
    if (argon2i_hash_encoded((uint32_t) opslimit, (uint32_t) (memlimit / 1024U),
                             (uint32_t) 1U, passwd, (size_t) passwdlen, salt,
                             sizeof salt, STR_HASHBYTES, out,
                             crypto_pwhash_argon2i_STRBYTES) != ARGON2_OK) {
        return -1; /* LCOV_EXCL_LINE */
    }
    return 0;
}