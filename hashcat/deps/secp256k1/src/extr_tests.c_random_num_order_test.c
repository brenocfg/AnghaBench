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
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_num ;

/* Variables and functions */
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void random_num_order_test(secp256k1_num *num) {
    secp256k1_scalar sc;
    random_scalar_order_test(&sc);
    secp256k1_scalar_get_num(num, &sc);
}