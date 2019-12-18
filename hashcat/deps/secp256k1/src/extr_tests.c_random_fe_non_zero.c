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
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  random_fe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 

void random_fe_non_zero(secp256k1_fe *nz) {
    int tries = 10;
    while (--tries >= 0) {
        random_fe(nz);
        secp256k1_fe_normalize(nz);
        if (!secp256k1_fe_is_zero(nz)) {
            break;
        }
    }
    /* Infinitesimal probability of spurious failure here */
    CHECK(tries >= 0);
}