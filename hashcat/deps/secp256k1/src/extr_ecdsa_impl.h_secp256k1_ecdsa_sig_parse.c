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
typedef  int /*<<< orphan*/  secp256k1_scalar ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_der_parse_integer (int /*<<< orphan*/ *,unsigned char const**,unsigned char const*) ; 
 scalar_t__ secp256k1_der_read_len (size_t*,unsigned char const**,unsigned char const*) ; 

__attribute__((used)) static int secp256k1_ecdsa_sig_parse(secp256k1_scalar *rr, secp256k1_scalar *rs, const unsigned char *sig, size_t size) {
    const unsigned char *sigend = sig + size;
    size_t rlen;
    if (sig == sigend || *(sig++) != 0x30) {
        /* The encoding doesn't start with a constructed sequence (X.690-0207 8.9.1). */
        return 0;
    }
    if (secp256k1_der_read_len(&rlen, &sig, sigend) == 0) {
        return 0;
    }
    if (rlen != (size_t)(sigend - sig)) {
        /* Tuple exceeds bounds or garage after tuple. */
        return 0;
    }

    if (!secp256k1_der_parse_integer(rr, &sig, sigend)) {
        return 0;
    }
    if (!secp256k1_der_parse_integer(rs, &sig, sigend)) {
        return 0;
    }

    if (sig != sigend) {
        /* Trailing garbage inside tuple. */
        return 0;
    }

    return 1;
}