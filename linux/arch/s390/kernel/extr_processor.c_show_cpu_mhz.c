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
struct seq_file {int dummy; } ;
struct cpu_info {int /*<<< orphan*/  cpu_mhz_static; int /*<<< orphan*/  cpu_mhz_dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_info ; 
 struct cpu_info* per_cpu_ptr (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_cpu_mhz(struct seq_file *m, unsigned long n)
{
	struct cpu_info *c = per_cpu_ptr(&cpu_info, n);

	seq_printf(m, "cpu MHz dynamic : %d\n", c->cpu_mhz_dynamic);
	seq_printf(m, "cpu MHz static  : %d\n", c->cpu_mhz_static);
}