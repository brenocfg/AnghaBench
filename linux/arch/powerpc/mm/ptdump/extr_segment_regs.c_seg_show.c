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
typedef  int u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int mfsrin (int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void seg_show(struct seq_file *m, int i)
{
	u32 val = mfsrin(i << 28);

	seq_printf(m, "0x%01x0000000-0x%01xfffffff ", i, i);
	seq_printf(m, "Kern key %d ", (val >> 30) & 1);
	seq_printf(m, "User key %d ", (val >> 29) & 1);
	if (val & 0x80000000) {
		seq_printf(m, "Device 0x%03x", (val >> 20) & 0x1ff);
		seq_printf(m, "-0x%05x", val & 0xfffff);
	} else {
		if (val & 0x10000000)
			seq_puts(m, "No Exec ");
		seq_printf(m, "VSID 0x%06x", val & 0xffffff);
	}
	seq_puts(m, "\n");
}