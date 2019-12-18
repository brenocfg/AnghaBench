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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kpssv2_release_secondary ; 
 int qcom_boot_secondary (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kpssv2_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	return qcom_boot_secondary(cpu, kpssv2_release_secondary);
}