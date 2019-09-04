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
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_3__ {int /*<<< orphan*/  num_n_bits; } ;

/* Variables and functions */
 int BITS_TO_BYTES (int /*<<< orphan*/ ) ; 

int uECC_curve_private_key_size(uECC_Curve curve) {
    return BITS_TO_BYTES(curve->num_n_bits);
}