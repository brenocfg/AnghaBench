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
struct cpu_cacheinfo {int dummy; } ;

/* Variables and functions */
 struct cpu_cacheinfo* ci_cacheinfo (unsigned int) ; 

struct cpu_cacheinfo *get_cpu_cacheinfo(unsigned int cpu)
{
	return ci_cacheinfo(cpu);
}