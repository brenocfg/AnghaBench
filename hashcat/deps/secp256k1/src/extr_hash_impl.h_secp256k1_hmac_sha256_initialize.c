#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_sha256 ;
struct TYPE_3__ {int /*<<< orphan*/  inner; int /*<<< orphan*/  outer; } ;
typedef  TYPE_1__ secp256k1_hmac_sha256 ;
typedef  int /*<<< orphan*/  rkey ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_sha256_finalize (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_sha256_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_sha256_write (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static void secp256k1_hmac_sha256_initialize(secp256k1_hmac_sha256 *hash, const unsigned char *key, size_t keylen) {
    size_t n;
    unsigned char rkey[64];
    if (keylen <= sizeof(rkey)) {
        memcpy(rkey, key, keylen);
        memset(rkey + keylen, 0, sizeof(rkey) - keylen);
    } else {
        secp256k1_sha256 sha256;
        secp256k1_sha256_initialize(&sha256);
        secp256k1_sha256_write(&sha256, key, keylen);
        secp256k1_sha256_finalize(&sha256, rkey);
        memset(rkey + 32, 0, 32);
    }

    secp256k1_sha256_initialize(&hash->outer);
    for (n = 0; n < sizeof(rkey); n++) {
        rkey[n] ^= 0x5c;
    }
    secp256k1_sha256_write(&hash->outer, rkey, sizeof(rkey));

    secp256k1_sha256_initialize(&hash->inner);
    for (n = 0; n < sizeof(rkey); n++) {
        rkey[n] ^= 0x5c ^ 0x36;
    }
    secp256k1_sha256_write(&hash->inner, rkey, sizeof(rkey));
    memset(rkey, 0, sizeof(rkey));
}