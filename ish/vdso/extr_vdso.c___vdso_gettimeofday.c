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

int __vdso_gettimeofday(void *timeval, void *timezone) {
    int result;
    __asm__("int $0x80" : "=a" (result) :
            "0" (78 /* __NR_gettimeofday */), "b" (timeval), "c" (timezone));
    return result;
}