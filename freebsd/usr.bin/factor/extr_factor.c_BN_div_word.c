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
typedef  int BN_ULONG ;
typedef  int BIGNUM ;

/* Variables and functions */

__attribute__((used)) static BN_ULONG
BN_div_word(BIGNUM *a, BN_ULONG b)
{
	BN_ULONG mod;

	mod = *a % b;
	*a /= b;
	return mod;
}