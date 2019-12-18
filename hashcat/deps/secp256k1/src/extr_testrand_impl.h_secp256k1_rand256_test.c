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
 int /*<<< orphan*/  secp256k1_rand_bytes_test (unsigned char*,int) ; 

__attribute__((used)) static void secp256k1_rand256_test(unsigned char *b32) {
    secp256k1_rand_bytes_test(b32, 32);
}