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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_BAT_ADDR (int) ; 
 int _PAGE_COHERENT ; 
 int _PAGE_NO_CACHE ; 
 int _PAGE_WRITETHRU ; 
 int pp_601 (int,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void bat_show_601(struct seq_file *m, int idx, u32 lower, u32 upper)
{
	u32 blpi = upper & 0xfffe0000;
	u32 k = (upper >> 2) & 3;
	u32 pp = upper & 3;
	phys_addr_t pbn = PHYS_BAT_ADDR(lower);
	u32 bsm = lower & 0x3ff;
	u32 size = (bsm + 1) << 17;

	seq_printf(m, "%d: ", idx);
	if (!(lower & 0x40)) {
		seq_puts(m, "        -\n");
		return;
	}

	seq_printf(m, "0x%08x-0x%08x ", blpi, blpi + size - 1);
#ifdef CONFIG_PHYS_64BIT
	seq_printf(m, "0x%016llx ", pbn);
#else
	seq_printf(m, "0x%08x ", pbn);
#endif

	seq_printf(m, "Kernel %s User %s", pp_601(k & 2, pp), pp_601(k & 1, pp));

	if (lower & _PAGE_WRITETHRU)
		seq_puts(m, "write through ");
	if (lower & _PAGE_NO_CACHE)
		seq_puts(m, "no cache ");
	if (lower & _PAGE_COHERENT)
		seq_puts(m, "coherent ");
	seq_puts(m, "\n");
}