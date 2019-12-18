#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_rfc6979_hmac_sha256 ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ bench_inv ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_rfc6979_hmac_sha256_generate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_rfc6979_hmac_sha256_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void bench_rfc6979_hmac_sha256(void* arg) {
    int i;
    bench_inv *data = (bench_inv*)arg;
    secp256k1_rfc6979_hmac_sha256 rng;

    for (i = 0; i < 20000; i++) {
        secp256k1_rfc6979_hmac_sha256_initialize(&rng, data->data, 64);
        secp256k1_rfc6979_hmac_sha256_generate(&rng, data->data, 32);
    }
}