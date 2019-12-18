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
 int crypto_simd_usable () ; 
 scalar_t__ have_simd ; 

__attribute__((used)) static bool aegis128_do_simd(void)
{
#ifdef CONFIG_CRYPTO_AEGIS128_SIMD
	if (have_simd)
		return crypto_simd_usable();
#endif
	return false;
}