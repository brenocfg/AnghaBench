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
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  assign_big_endian (unsigned char*,int,int) ; 
 int secp256k1_rand_bits (int) ; 
 int /*<<< orphan*/  secp256k1_rand_bytes_test (unsigned char*,size_t) ; 
 int secp256k1_rand_int (int) ; 

__attribute__((used)) static void random_ber_signature(unsigned char *sig, size_t *len, int* certainly_der, int* certainly_not_der) {
    int der;
    int nlow[2], nlen[2], nlenlen[2], nhbit[2], nhbyte[2], nzlen[2];
    size_t tlen, elen, glen;
    int indet;
    int n;

    *len = 0;
    der = secp256k1_rand_bits(2) == 0;
    *certainly_der = der;
    *certainly_not_der = 0;
    indet = der ? 0 : secp256k1_rand_int(10) == 0;

    for (n = 0; n < 2; n++) {
        /* We generate two classes of numbers: nlow==1 "low" ones (up to 32 bytes), nlow==0 "high" ones (32 bytes with 129 top bits set, or larger than 32 bytes) */
        nlow[n] = der ? 1 : (secp256k1_rand_bits(3) != 0);
        /* The length of the number in bytes (the first byte of which will always be nonzero) */
        nlen[n] = nlow[n] ? secp256k1_rand_int(33) : 32 + secp256k1_rand_int(200) * secp256k1_rand_int(8) / 8;
        CHECK(nlen[n] <= 232);
        /* The top bit of the number. */
        nhbit[n] = (nlow[n] == 0 && nlen[n] == 32) ? 1 : (nlen[n] == 0 ? 0 : secp256k1_rand_bits(1));
        /* The top byte of the number (after the potential hardcoded 16 0xFF characters for "high" 32 bytes numbers) */
        nhbyte[n] = nlen[n] == 0 ? 0 : (nhbit[n] ? 128 + secp256k1_rand_bits(7) : 1 + secp256k1_rand_int(127));
        /* The number of zero bytes in front of the number (which is 0 or 1 in case of DER, otherwise we extend up to 300 bytes) */
        nzlen[n] = der ? ((nlen[n] == 0 || nhbit[n]) ? 1 : 0) : (nlow[n] ? secp256k1_rand_int(3) : secp256k1_rand_int(300 - nlen[n]) * secp256k1_rand_int(8) / 8);
        if (nzlen[n] > ((nlen[n] == 0 || nhbit[n]) ? 1 : 0)) {
            *certainly_not_der = 1;
        }
        CHECK(nlen[n] + nzlen[n] <= 300);
        /* The length of the length descriptor for the number. 0 means short encoding, anything else is long encoding. */
        nlenlen[n] = nlen[n] + nzlen[n] < 128 ? 0 : (nlen[n] + nzlen[n] < 256 ? 1 : 2);
        if (!der) {
            /* nlenlen[n] max 127 bytes */
            int add = secp256k1_rand_int(127 - nlenlen[n]) * secp256k1_rand_int(16) * secp256k1_rand_int(16) / 256;
            nlenlen[n] += add;
            if (add != 0) {
                *certainly_not_der = 1;
            }
        }
        CHECK(nlen[n] + nzlen[n] + nlenlen[n] <= 427);
    }

    /* The total length of the data to go, so far */
    tlen = 2 + nlenlen[0] + nlen[0] + nzlen[0] + 2 + nlenlen[1] + nlen[1] + nzlen[1];
    CHECK(tlen <= 856);

    /* The length of the garbage inside the tuple. */
    elen = (der || indet) ? 0 : secp256k1_rand_int(980 - tlen) * secp256k1_rand_int(8) / 8;
    if (elen != 0) {
        *certainly_not_der = 1;
    }
    tlen += elen;
    CHECK(tlen <= 980);

    /* The length of the garbage after the end of the tuple. */
    glen = der ? 0 : secp256k1_rand_int(990 - tlen) * secp256k1_rand_int(8) / 8;
    if (glen != 0) {
        *certainly_not_der = 1;
    }
    CHECK(tlen + glen <= 990);

    /* Write the tuple header. */
    sig[(*len)++] = 0x30;
    if (indet) {
        /* Indeterminate length */
        sig[(*len)++] = 0x80;
        *certainly_not_der = 1;
    } else {
        int tlenlen = tlen < 128 ? 0 : (tlen < 256 ? 1 : 2);
        if (!der) {
            int add = secp256k1_rand_int(127 - tlenlen) * secp256k1_rand_int(16) * secp256k1_rand_int(16) / 256;
            tlenlen += add;
            if (add != 0) {
                *certainly_not_der = 1;
            }
        }
        if (tlenlen == 0) {
            /* Short length notation */
            sig[(*len)++] = tlen;
        } else {
            /* Long length notation */
            sig[(*len)++] = 128 + tlenlen;
            assign_big_endian(sig + *len, tlenlen, tlen);
            *len += tlenlen;
        }
        tlen += tlenlen;
    }
    tlen += 2;
    CHECK(tlen + glen <= 1119);

    for (n = 0; n < 2; n++) {
        /* Write the integer header. */
        sig[(*len)++] = 0x02;
        if (nlenlen[n] == 0) {
            /* Short length notation */
            sig[(*len)++] = nlen[n] + nzlen[n];
        } else {
            /* Long length notation. */
            sig[(*len)++] = 128 + nlenlen[n];
            assign_big_endian(sig + *len, nlenlen[n], nlen[n] + nzlen[n]);
            *len += nlenlen[n];
        }
        /* Write zero padding */
        while (nzlen[n] > 0) {
            sig[(*len)++] = 0x00;
            nzlen[n]--;
        }
        if (nlen[n] == 32 && !nlow[n]) {
            /* Special extra 16 0xFF bytes in "high" 32-byte numbers */
            int i;
            for (i = 0; i < 16; i++) {
                sig[(*len)++] = 0xFF;
            }
            nlen[n] -= 16;
        }
        /* Write first byte of number */
        if (nlen[n] > 0) {
            sig[(*len)++] = nhbyte[n];
            nlen[n]--;
        }
        /* Generate remaining random bytes of number */
        secp256k1_rand_bytes_test(sig + *len, nlen[n]);
        *len += nlen[n];
        nlen[n] = 0;
    }

    /* Generate random garbage inside tuple. */
    secp256k1_rand_bytes_test(sig + *len, elen);
    *len += elen;

    /* Generate end-of-contents bytes. */
    if (indet) {
        sig[(*len)++] = 0;
        sig[(*len)++] = 0;
        tlen += 2;
    }
    CHECK(tlen + glen <= 1121);

    /* Generate random garbage outside tuple. */
    secp256k1_rand_bytes_test(sig + *len, glen);
    *len += glen;
    tlen += glen;
    CHECK(tlen <= 1121);
    CHECK(tlen == *len);
}