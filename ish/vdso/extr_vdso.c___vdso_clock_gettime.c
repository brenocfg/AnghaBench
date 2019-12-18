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
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */

int __vdso_clock_gettime(clockid_t clock, void *timespec) {
    int result;
    __asm__("int $0x80" : "=a" (result) :
            "0" (265 /* __NR_clock_gettime */), "b" (clock), "c" (timespec));
    return result;
}