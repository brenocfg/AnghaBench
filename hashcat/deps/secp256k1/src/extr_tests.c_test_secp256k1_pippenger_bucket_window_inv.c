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
 int PIPPENGER_MAX_BUCKET_WINDOW ; 
 int secp256k1_pippenger_bucket_window (scalar_t__) ; 
 scalar_t__ secp256k1_pippenger_bucket_window_inv (int) ; 

void test_secp256k1_pippenger_bucket_window_inv(void) {
    int i;

    CHECK(secp256k1_pippenger_bucket_window_inv(0) == 0);
    for(i = 1; i <= PIPPENGER_MAX_BUCKET_WINDOW; i++) {
#ifdef USE_ENDOMORPHISM
        /* Bucket_window of 8 is not used with endo */
        if (i == 8) {
            continue;
        }
#endif
        CHECK(secp256k1_pippenger_bucket_window(secp256k1_pippenger_bucket_window_inv(i)) == i);
        if (i != PIPPENGER_MAX_BUCKET_WINDOW) {
            CHECK(secp256k1_pippenger_bucket_window(secp256k1_pippenger_bucket_window_inv(i)+1) > i);
        }
    }
}