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
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
timespec_add(struct timespec *tsa, struct timespec *tsb)
{

        tsa->tv_sec += tsb->tv_sec;
        tsa->tv_nsec += tsb->tv_nsec;
        if (tsa->tv_nsec >= 1000000000) {
                tsa->tv_sec++;
                tsa->tv_nsec -= 1000000000;
        }
}