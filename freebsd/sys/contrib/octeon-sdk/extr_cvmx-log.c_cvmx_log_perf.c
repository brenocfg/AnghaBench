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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_LOG_TYPE_PERF ; 
 int __cvmx_log_build_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __cvmx_log_write (int) ; 

void cvmx_log_perf(void)
{
    uint64_t control1;
    uint64_t control2;
    uint64_t data1;
    uint64_t data2;
    asm ("dmfc0 %0, $25, 1\n" : "=r"(data1));
    asm ("dmfc0 %0, $25, 3\n" : "=r"(data2));
    asm ("mfc0 %0, $25, 0\n" : "=r"(control1));
    asm ("mfc0 %0, $25, 2\n" : "=r"(control2));
    __cvmx_log_write(__cvmx_log_build_header(CVMX_LOG_TYPE_PERF, 3));
    __cvmx_log_write(((control1 & 0xffffffff) << 32) | (control2 & 0xffffffff));
    __cvmx_log_write(data1);
    __cvmx_log_write(data2);
}