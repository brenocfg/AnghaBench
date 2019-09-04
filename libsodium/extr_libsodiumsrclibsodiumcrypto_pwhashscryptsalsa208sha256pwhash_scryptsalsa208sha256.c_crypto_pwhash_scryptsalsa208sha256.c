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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned long long crypto_pwhash_scryptsalsa208sha256_BYTES_MAX ; 
 unsigned long long crypto_pwhash_scryptsalsa208sha256_BYTES_MIN ; 
 unsigned long long crypto_pwhash_scryptsalsa208sha256_PASSWD_MAX ; 
 int /*<<< orphan*/  crypto_pwhash_scryptsalsa208sha256_SALTBYTES ; 
 int crypto_pwhash_scryptsalsa208sha256_ll (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int,unsigned char* const,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (unsigned char* const,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ pickparams (unsigned long long,size_t,int*,int*,int*) ; 

int
crypto_pwhash_scryptsalsa208sha256(unsigned char *const       out,
                                   unsigned long long         outlen,
                                   const char *const          passwd,
                                   unsigned long long         passwdlen,
                                   const unsigned char *const salt,
                                   unsigned long long opslimit, size_t memlimit)
{
    uint32_t N_log2;
    uint32_t p;
    uint32_t r;

    memset(out, 0, outlen);
    if (passwdlen > crypto_pwhash_scryptsalsa208sha256_PASSWD_MAX ||
        outlen > crypto_pwhash_scryptsalsa208sha256_BYTES_MAX) {
        errno = EFBIG; /* LCOV_EXCL_LINE */
        return -1;     /* LCOV_EXCL_LINE */
    }
    if (outlen < crypto_pwhash_scryptsalsa208sha256_BYTES_MIN ||
        pickparams(opslimit, memlimit, &N_log2, &p, &r) != 0) {
        errno = EINVAL; /* LCOV_EXCL_LINE */
        return -1;      /* LCOV_EXCL_LINE */
    }
    return crypto_pwhash_scryptsalsa208sha256_ll(
        (const uint8_t *) passwd, (size_t) passwdlen, (const uint8_t *) salt,
        crypto_pwhash_scryptsalsa208sha256_SALTBYTES, (uint64_t)(1) << N_log2,
        r, p, out, (size_t) outlen);
}