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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int CPUID2_SSE42 ; 
 scalar_t__ ID_AA64ISAR0_CRC32_NONE ; 
 scalar_t__ ID_AA64ISAR0_CRC32_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv8_crc32c (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  id_aa64isar0_el1 ; 
 int /*<<< orphan*/  multitable_crc32c (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  singletable_crc32c (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  sse42_crc32c (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

uint32_t
calculate_crc32c(uint32_t crc32c,
    const unsigned char *buffer,
    unsigned int length)
{
#ifdef _KERNEL
#if defined(__amd64__) || defined(__i386__)
	if ((cpu_feature2 & CPUID2_SSE42) != 0) {
		return (sse42_crc32c(crc32c, buffer, length));
	} else
#endif
#if defined(__aarch64__)
	uint64_t reg;

	/*
	 * We only test for CRC32 support on the CPU with index 0 assuming that
	 * this applies to all CPUs.
	 */
	reg = READ_SPECIALREG(id_aa64isar0_el1);
	if (ID_AA64ISAR0_CRC32_VAL(reg) != ID_AA64ISAR0_CRC32_NONE) {
		return (armv8_crc32c(crc32c, buffer, length));
	} else
#endif
#endif /* _KERNEL */
	if (length < 4) {
		return (singletable_crc32c(crc32c, buffer, length));
	} else {
		return (multitable_crc32c(crc32c, buffer, length));
	}
}