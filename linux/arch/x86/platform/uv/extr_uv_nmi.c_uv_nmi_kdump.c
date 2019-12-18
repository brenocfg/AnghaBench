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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  uv_nmi_kexec_failed ; 

__attribute__((used)) static inline void uv_nmi_kdump(int cpu, int master, struct pt_regs *regs)
{
	if (master)
		pr_err("UV: NMI kdump: KEXEC not supported in this kernel\n");
	atomic_set(&uv_nmi_kexec_failed, 1);
}