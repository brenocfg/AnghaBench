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
 int /*<<< orphan*/  ARGON2_OK ; 
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  argon2i_hash_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,size_t,unsigned char const* const,size_t,unsigned char* const,size_t) ; 
#define  crypto_pwhash_argon2i_ALG_ARGON2I13 128 
 unsigned long long crypto_pwhash_argon2i_BYTES_MAX ; 
 unsigned long long crypto_pwhash_argon2i_BYTES_MIN ; 
 size_t crypto_pwhash_argon2i_MEMLIMIT_MAX ; 
 size_t crypto_pwhash_argon2i_MEMLIMIT_MIN ; 
 unsigned long long crypto_pwhash_argon2i_OPSLIMIT_MAX ; 
 unsigned long long crypto_pwhash_argon2i_OPSLIMIT_MIN ; 
 unsigned long long crypto_pwhash_argon2i_PASSWD_MAX ; 
 unsigned long long crypto_pwhash_argon2i_PASSWD_MIN ; 
 int /*<<< orphan*/  crypto_pwhash_argon2i_SALTBYTES ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (unsigned char* const,int /*<<< orphan*/ ,unsigned long long) ; 

int
crypto_pwhash_argon2i(unsigned char *const out, unsigned long long outlen,
                      const char *const passwd, unsigned long long passwdlen,
                      const unsigned char *const salt,
                      unsigned long long opslimit, size_t memlimit, int alg)
{
    memset(out, 0, outlen);
    if (outlen > crypto_pwhash_argon2i_BYTES_MAX) {
        errno = EFBIG;
        return -1;
    }
    if (outlen < crypto_pwhash_argon2i_BYTES_MIN) {
        errno = EINVAL;
        return -1;
    }
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
    switch (alg) {
    case crypto_pwhash_argon2i_ALG_ARGON2I13:
        if (argon2i_hash_raw((uint32_t) opslimit, (uint32_t) (memlimit / 1024U),
                             (uint32_t) 1U, passwd, (size_t) passwdlen, salt,
                             (size_t) crypto_pwhash_argon2i_SALTBYTES, out,
                             (size_t) outlen) != ARGON2_OK) {
            return -1; /* LCOV_EXCL_LINE */
        }
        return 0;
    default:
        errno = EINVAL;
        return -1;
    }
}