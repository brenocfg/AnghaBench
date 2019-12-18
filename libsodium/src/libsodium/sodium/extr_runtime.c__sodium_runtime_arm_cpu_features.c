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
typedef  scalar_t__ cpu_type_t ;
typedef  scalar_t__ cpu_subtype_t ;
struct TYPE_3__ {int has_neon; int has_armcrypto; } ;
typedef  TYPE_1__ CPUFeatures ;

/* Variables and functions */
 int ANDROID_CPU_ARM_FEATURE_AES ; 
 int ANDROID_CPU_ARM_FEATURE_NEON ; 
 int /*<<< orphan*/  AT_HWCAP ; 
 int /*<<< orphan*/  AT_HWCAP2 ; 
 scalar_t__ CPU_SUBTYPE_ARM64E ; 
 scalar_t__ CPU_SUBTYPE_ARM64_V8 ; 
 scalar_t__ CPU_TYPE_ARM64 ; 
 int android_getCpuFeatures () ; 
 long getauxval (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_sodium_runtime_arm_cpu_features(CPUFeatures * const cpu_features)
{
    cpu_features->has_neon = 0;
    cpu_features->has_armcrypto = 0;

#ifndef __ARM_ARCH
    return -1; /* LCOV_EXCL_LINE */
#endif

#if defined(__ARM_NEON) || defined(__aarch64__)
    cpu_features->has_neon = 1;
#elif defined(HAVE_ANDROID_GETCPUFEATURES) && defined(ANDROID_CPU_ARM_FEATURE_NEON)
    cpu_features->has_neon =
        (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON) != 0x0;
#elif defined(HAVE_GETAUXVAL) && defined(AT_HWCAP) && defined(__aarch64__)
    cpu_features->has_neon = (getauxval(AT_HWCAP) & (1L << 1)) != 0;
#elif defined(HAVE_GETAUXVAL) && defined(AT_HWCAP) && defined(__arm__)
    cpu_features->has_neon = (getauxval(AT_HWCAP) & (1L << 12)) != 0;
#endif

    if (cpu_features->has_neon == 0) {
        return 0;
    }

#if __ARM_FEATURE_CRYPTO
    cpu_features->has_armcrypto = 1;
#elif defined(__APPLE__) && defined(CPU_TYPE_ARM64) && defined(CPU_SUBTYPE_ARM64E)
    {
        cpu_type_t    cpu_type;
        cpu_subtype_t cpu_subtype;
        size_t        cpu_type_len = sizeof cpu_type;
        size_t        cpu_subtype_len = sizeof cpu_subtype;

        if (sysctlbyname("hw.cputype", &cpu_type, &cpu_type_len,
                         NULL, 0) == 0 && cpu_type == CPU_TYPE_ARM64 &&
            sysctlbyname("hw.cpusubtype", &cpu_subtype, &cpu_subtype_len,
                         NULL, 0) == 0 &&
            (cpu_subtype == CPU_SUBTYPE_ARM64E ||
                cpu_subtype == CPU_SUBTYPE_ARM64_V8)) {
            cpu_features->has_armcrypto = 1;
        }
    }
#elif defined(HAVE_ANDROID_GETCPUFEATURES) && defined(ANDROID_CPU_ARM_FEATURE_AES)
    cpu_features->has_armcrypto =
        (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_AES) != 0x0;
#elif defined(HAVE_GETAUXVAL) && defined(AT_HWCAP) && defined(__aarch64__)
    cpu_features->has_armcrypto = (getauxval(AT_HWCAP) & (1L << 3)) != 0;
#elif defined(HAVE_GETAUXVAL) && defined(AT_HWCAP2) && defined(__arm__)
    cpu_features->has_armcrypto = (getauxval(AT_HWCAP2) & (1L << 0)) != 0;
#endif

    return 0;
}