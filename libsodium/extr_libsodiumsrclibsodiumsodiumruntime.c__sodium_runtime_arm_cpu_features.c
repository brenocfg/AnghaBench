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
struct TYPE_3__ {scalar_t__ has_neon; } ;
typedef  TYPE_1__ CPUFeatures ;

/* Variables and functions */

__attribute__((used)) static int
_sodium_runtime_arm_cpu_features(CPUFeatures * const cpu_features)
{
#ifndef __arm__
    cpu_features->has_neon = 0;
    return -1;
#else
# ifdef __APPLE__
#  ifdef __ARM_NEON__
    cpu_features->has_neon = 1;
#  else
    cpu_features->has_neon = 0;
#  endif
# elif defined(HAVE_ANDROID_GETCPUFEATURES) && \
    defined(ANDROID_CPU_ARM_FEATURE_NEON)
    cpu_features->has_neon =
        (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON) != 0x0;
# else
    cpu_features->has_neon = 0;
# endif
    return 0;
#endif
}