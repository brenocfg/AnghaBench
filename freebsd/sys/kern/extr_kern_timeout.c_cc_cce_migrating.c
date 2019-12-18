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
struct callout_cpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPUBLOCK ; 
 scalar_t__ cc_migration_cpu (struct callout_cpu*,int) ; 

__attribute__((used)) static int
cc_cce_migrating(struct callout_cpu *cc, int direct)
{

#ifdef SMP
	return (cc_migration_cpu(cc, direct) != CPUBLOCK);
#else
	return (0);
#endif
}