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
 int /*<<< orphan*/  ecmult_const_chain_multiply () ; 
 int /*<<< orphan*/  ecmult_const_commutativity () ; 
 int /*<<< orphan*/  ecmult_const_mult_zero_one () ; 
 int /*<<< orphan*/  ecmult_const_random_mult () ; 

void run_ecmult_const_tests(void) {
    ecmult_const_mult_zero_one();
    ecmult_const_random_mult();
    ecmult_const_commutativity();
    ecmult_const_chain_multiply();
}