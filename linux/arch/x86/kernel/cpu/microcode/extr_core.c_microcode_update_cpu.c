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
struct ucode_cpu_info {scalar_t__ valid; } ;
typedef  enum ucode_state { ____Placeholder_ucode_state } ucode_state ;

/* Variables and functions */
 int /*<<< orphan*/  collect_cpu_info (int) ; 
 int microcode_init_cpu (int,int) ; 
 int microcode_resume_cpu (int) ; 
 struct ucode_cpu_info* ucode_cpu_info ; 

__attribute__((used)) static enum ucode_state microcode_update_cpu(int cpu)
{
	struct ucode_cpu_info *uci = ucode_cpu_info + cpu;

	/* Refresh CPU microcode revision after resume. */
	collect_cpu_info(cpu);

	if (uci->valid)
		return microcode_resume_cpu(cpu);

	return microcode_init_cpu(cpu, false);
}