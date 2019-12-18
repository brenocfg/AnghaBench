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
typedef  int /*<<< orphan*/  secp256k1_num ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_num_negate (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_rand_bits (int) ; 

void random_num_negate(secp256k1_num *num) {
    if (secp256k1_rand_bits(1)) {
        secp256k1_num_negate(num);
    }
}