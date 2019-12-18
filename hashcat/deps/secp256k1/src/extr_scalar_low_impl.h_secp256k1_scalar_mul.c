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
typedef  int secp256k1_scalar ;

/* Variables and functions */
 int const EXHAUSTIVE_TEST_ORDER ; 

__attribute__((used)) static void secp256k1_scalar_mul(secp256k1_scalar *r, const secp256k1_scalar *a, const secp256k1_scalar *b) {
    *r = (*a * *b) % EXHAUSTIVE_TEST_ORDER;
}