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
struct TYPE_3__ {int /*<<< orphan*/  outer; int /*<<< orphan*/  inner; } ;
typedef  TYPE_1__ secp256k1_hmac_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_sha256_finalize (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_sha256_write (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void secp256k1_hmac_sha256_finalize(secp256k1_hmac_sha256 *hash, unsigned char *out32) {
    unsigned char temp[32];
    secp256k1_sha256_finalize(&hash->inner, temp);
    secp256k1_sha256_write(&hash->outer, temp, 32);
    memset(temp, 0, 32);
    secp256k1_sha256_finalize(&hash->outer, out32);
}