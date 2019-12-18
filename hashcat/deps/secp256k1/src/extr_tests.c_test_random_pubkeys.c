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
typedef  int /*<<< orphan*/  secp256k1_ge ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  ge_equals_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int secp256k1_eckey_pubkey_parse (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int secp256k1_eckey_pubkey_serialize (int /*<<< orphan*/ *,unsigned char*,size_t*,int) ; 
 int /*<<< orphan*/  secp256k1_rand256 (unsigned char*) ; 
 size_t secp256k1_rand_bits (int) ; 

void test_random_pubkeys(void) {
    secp256k1_ge elem;
    secp256k1_ge elem2;
    unsigned char in[65];
    /* Generate some randomly sized pubkeys. */
    size_t len = secp256k1_rand_bits(2) == 0 ? 65 : 33;
    if (secp256k1_rand_bits(2) == 0) {
        len = secp256k1_rand_bits(6);
    }
    if (len == 65) {
      in[0] = secp256k1_rand_bits(1) ? 4 : (secp256k1_rand_bits(1) ? 6 : 7);
    } else {
      in[0] = secp256k1_rand_bits(1) ? 2 : 3;
    }
    if (secp256k1_rand_bits(3) == 0) {
        in[0] = secp256k1_rand_bits(8);
    }
    if (len > 1) {
        secp256k1_rand256(&in[1]);
    }
    if (len > 33) {
        secp256k1_rand256(&in[33]);
    }
    if (secp256k1_eckey_pubkey_parse(&elem, in, len)) {
        unsigned char out[65];
        unsigned char firstb;
        int res;
        size_t size = len;
        firstb = in[0];
        /* If the pubkey can be parsed, it should round-trip... */
        CHECK(secp256k1_eckey_pubkey_serialize(&elem, out, &size, len == 33));
        CHECK(size == len);
        CHECK(memcmp(&in[1], &out[1], len-1) == 0);
        /* ... except for the type of hybrid inputs. */
        if ((in[0] != 6) && (in[0] != 7)) {
            CHECK(in[0] == out[0]);
        }
        size = 65;
        CHECK(secp256k1_eckey_pubkey_serialize(&elem, in, &size, 0));
        CHECK(size == 65);
        CHECK(secp256k1_eckey_pubkey_parse(&elem2, in, size));
        ge_equals_ge(&elem,&elem2);
        /* Check that the X9.62 hybrid type is checked. */
        in[0] = secp256k1_rand_bits(1) ? 6 : 7;
        res = secp256k1_eckey_pubkey_parse(&elem2, in, size);
        if (firstb == 2 || firstb == 3) {
            if (in[0] == firstb + 4) {
              CHECK(res);
            } else {
              CHECK(!res);
            }
        }
        if (res) {
            ge_equals_ge(&elem,&elem2);
            CHECK(secp256k1_eckey_pubkey_serialize(&elem, out, &size, 0));
            CHECK(memcmp(&in[1], &out[1], 64) == 0);
        }
    }
}