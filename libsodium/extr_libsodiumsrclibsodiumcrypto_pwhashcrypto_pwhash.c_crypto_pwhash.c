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
 int /*<<< orphan*/  EINVAL ; 
#define  crypto_pwhash_ALG_ARGON2I13 129 
#define  crypto_pwhash_ALG_ARGON2ID13 128 
 int crypto_pwhash_argon2i (unsigned char* const,unsigned long long,char const* const,unsigned long long,unsigned char const* const,unsigned long long,size_t,int) ; 
 int crypto_pwhash_argon2id (unsigned char* const,unsigned long long,char const* const,unsigned long long,unsigned char const* const,unsigned long long,size_t,int) ; 
 int /*<<< orphan*/  errno ; 

int
crypto_pwhash(unsigned char * const out, unsigned long long outlen,
              const char * const passwd, unsigned long long passwdlen,
              const unsigned char * const salt,
              unsigned long long opslimit, size_t memlimit, int alg)
{
    switch (alg) {
    case crypto_pwhash_ALG_ARGON2I13:
        return crypto_pwhash_argon2i(out, outlen, passwd, passwdlen, salt,
                                     opslimit, memlimit, alg);
    case crypto_pwhash_ALG_ARGON2ID13:
        return crypto_pwhash_argon2id(out, outlen, passwd, passwdlen, salt,
                                      opslimit, memlimit, alg);
    default:
        errno = EINVAL;
        return -1;
    }
}