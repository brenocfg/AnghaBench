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
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int cputick2usec (int) ; 

__attribute__((used)) static inline void 
cputick2timespec(uint64_t runtime, struct timespec *ats)
{
	runtime = cputick2usec(runtime);
	ats->tv_sec = runtime / 1000000;
	ats->tv_nsec = runtime % 1000000 * 1000;
}