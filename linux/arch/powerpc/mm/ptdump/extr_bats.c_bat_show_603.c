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
typedef  int phys_addr_t ;

/* Variables and functions */
 int BPP_RW ; 
 int BPP_RX ; 
 int PHYS_BAT_ADDR (int) ; 
 int _PAGE_COHERENT ; 
 int _PAGE_GUARDED ; 
 int _PAGE_NO_CACHE ; 
 int _PAGE_WRITETHRU ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bat_show_603(struct seq_file *m, int idx, u32 lower, u32 upper, bool is_d)
{
	u32 bepi = upper & 0xfffe0000;
	u32 bl = (upper >> 2) & 0x7ff;
	u32 k = upper & 3;
	phys_addr_t brpn = PHYS_BAT_ADDR(lower);
	u32 size = (bl + 1) << 17;

	seq_printf(m, "%d: ", idx);
	if (k == 0) {
		seq_puts(m, "        -\n");
		return;
	}

	seq_printf(m, "0x%08x-0x%08x ", bepi, bepi + size - 1);
#ifdef CONFIG_PHYS_64BIT
	seq_printf(m, "0x%016llx ", brpn);
#else
	seq_printf(m, "0x%08x ", brpn);
#endif

	if (k == 1)
		seq_puts(m, "User ");
	else if (k == 2)
		seq_puts(m, "Kernel ");
	else
		seq_puts(m, "Kernel/User ");

	if (lower & BPP_RX)
		seq_puts(m, is_d ? "RO " : "EXEC ");
	else if (lower & BPP_RW)
		seq_puts(m, is_d ? "RW " : "EXEC ");
	else
		seq_puts(m, is_d ? "NA " : "NX   ");

	if (lower & _PAGE_WRITETHRU)
		seq_puts(m, "write through ");
	if (lower & _PAGE_NO_CACHE)
		seq_puts(m, "no cache ");
	if (lower & _PAGE_COHERENT)
		seq_puts(m, "coherent ");
	if (lower & _PAGE_GUARDED)
		seq_puts(m, "guarded ");
	seq_puts(m, "\n");
}