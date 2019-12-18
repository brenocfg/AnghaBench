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
 int /*<<< orphan*/  AES ; 
 int /*<<< orphan*/  CONFIG_ARM64 ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 int aegis128_have_aes_insn ; 
 int /*<<< orphan*/  cpu_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_have_feature (int /*<<< orphan*/ ) ; 

bool crypto_aegis128_have_simd(void)
{
	if (cpu_have_feature(cpu_feature(AES))) {
		aegis128_have_aes_insn = 1;
		return true;
	}
	return IS_ENABLED(CONFIG_ARM64);
}