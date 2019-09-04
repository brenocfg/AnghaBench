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

__attribute__((used)) static void
_cpuid(unsigned int cpu_info[4U], const unsigned int cpu_info_type)
{
#if defined(_MSC_VER) && \
    (defined(_M_X64) || defined(_M_AMD64) || defined(_M_IX86))
    __cpuid((int *) cpu_info, cpu_info_type);
#elif defined(HAVE_CPUID)
    cpu_info[0] = cpu_info[1] = cpu_info[2] = cpu_info[3] = 0;
# ifdef __i386__
    __asm__ __volatile__(
        "pushfl; pushfl; "
        "popl %0; "
        "movl %0, %1; xorl %2, %0; "
        "pushl %0; "
        "popfl; pushfl; popl %0; popfl"
        : "=&r"(cpu_info[0]), "=&r"(cpu_info[1])
        : "i"(0x200000));
    if (((cpu_info[0] ^ cpu_info[1]) & 0x200000) == 0x0) {
        return; /* LCOV_EXCL_LINE */
    }
# endif
# ifdef __i386__
    __asm__ __volatile__("xchgl %%ebx, %k1; cpuid; xchgl %%ebx, %k1"
                         : "=a"(cpu_info[0]), "=&r"(cpu_info[1]),
                           "=c"(cpu_info[2]), "=d"(cpu_info[3])
                         : "0"(cpu_info_type), "2"(0U));
# elif defined(__x86_64__)
    __asm__ __volatile__("xchgq %%rbx, %q1; cpuid; xchgq %%rbx, %q1"
                         : "=a"(cpu_info[0]), "=&r"(cpu_info[1]),
                           "=c"(cpu_info[2]), "=d"(cpu_info[3])
                         : "0"(cpu_info_type), "2"(0U));
# else
    __asm__ __volatile__("cpuid"
                         : "=a"(cpu_info[0]), "=b"(cpu_info[1]),
                           "=c"(cpu_info[2]), "=d"(cpu_info[3])
                         : "0"(cpu_info_type), "2"(0U));
# endif
#else
    (void) cpu_info_type;
    cpu_info[0] = cpu_info[1] = cpu_info[2] = cpu_info[3] = 0;
#endif
}