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
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;

/* Variables and functions */

size_t
crypto_generichash_blake2b_statebytes(void)
{
    return (sizeof(crypto_generichash_blake2b_state) + (size_t) 63U)
        & ~(size_t) 63U;
}