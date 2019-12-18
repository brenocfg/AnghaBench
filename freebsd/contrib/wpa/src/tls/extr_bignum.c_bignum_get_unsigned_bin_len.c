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
struct bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 size_t mp_unsigned_bin_size (int /*<<< orphan*/ *) ; 

size_t bignum_get_unsigned_bin_len(struct bignum *n)
{
	return mp_unsigned_bin_size((mp_int *) n);
}