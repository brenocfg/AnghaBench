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
typedef  int u64 ;
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct mvebu_mbus_state {scalar_t__ sdramwins_base; } ;

/* Variables and functions */
 int DDR_BASE_CS_HIGH_MASK ; 
 int DDR_BASE_CS_LOW_MASK ; 
 scalar_t__ DDR_BASE_CS_OFF (int) ; 
 int DDR_SIZE_CS_MASK ; 
 scalar_t__ DDR_SIZE_CS_OFF (int) ; 
 int DDR_SIZE_CS_SHIFT ; 
 int DDR_SIZE_ENABLED ; 
 int DDR_SIZE_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int mvebu_sdram_debug_show_orion(struct mvebu_mbus_state *mbus,
					struct seq_file *seq, void *v)
{
	int i;

	for (i = 0; i < 4; i++) {
		u32 basereg = readl(mbus->sdramwins_base + DDR_BASE_CS_OFF(i));
		u32 sizereg = readl(mbus->sdramwins_base + DDR_SIZE_CS_OFF(i));
		u64 base;
		u32 size;

		if (!(sizereg & DDR_SIZE_ENABLED)) {
			seq_printf(seq, "[%d] disabled\n", i);
			continue;
		}

		base = ((u64)basereg & DDR_BASE_CS_HIGH_MASK) << 32;
		base |= basereg & DDR_BASE_CS_LOW_MASK;
		size = (sizereg | ~DDR_SIZE_MASK);

		seq_printf(seq, "[%d] %016llx - %016llx : cs%d\n",
			   i, (unsigned long long)base,
			   (unsigned long long)base + size + 1,
			   (sizereg & DDR_SIZE_CS_MASK) >> DDR_SIZE_CS_SHIFT);
	}

	return 0;
}