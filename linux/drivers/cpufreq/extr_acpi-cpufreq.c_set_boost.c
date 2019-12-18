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
 int /*<<< orphan*/  boost_set_msr_each ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

__attribute__((used)) static int set_boost(int val)
{
	get_online_cpus();
	on_each_cpu(boost_set_msr_each, (void *)(long)val, 1);
	put_online_cpus();
	pr_debug("Core Boosting %sabled.\n", val ? "en" : "dis");

	return 0;
}