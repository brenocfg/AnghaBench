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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_b32 (unsigned char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int secp256k1_ecdsa_sig_serialize(unsigned char *sig, size_t *size, const secp256k1_scalar* ar, const secp256k1_scalar* as) {
    unsigned char r[33] = {0}, s[33] = {0};
    unsigned char *rp = r, *sp = s;
    size_t lenR = 33, lenS = 33;
    secp256k1_scalar_get_b32(&r[1], ar);
    secp256k1_scalar_get_b32(&s[1], as);
    while (lenR > 1 && rp[0] == 0 && rp[1] < 0x80) { lenR--; rp++; }
    while (lenS > 1 && sp[0] == 0 && sp[1] < 0x80) { lenS--; sp++; }
    if (*size < 6+lenS+lenR) {
        *size = 6 + lenS + lenR;
        return 0;
    }
    *size = 6 + lenS + lenR;
    sig[0] = 0x30;
    sig[1] = 4 + lenS + lenR;
    sig[2] = 0x02;
    sig[3] = lenR;
    memcpy(sig+4, rp, lenR);
    sig[4+lenR] = 0x02;
    sig[5+lenR] = lenS;
    memcpy(sig+lenR+6, sp, lenS);
    return 1;
}