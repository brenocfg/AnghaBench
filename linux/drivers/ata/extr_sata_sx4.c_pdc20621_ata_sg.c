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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int ATA_PRD_EOT ; 
 unsigned int PDC_20621_DIMM_BASE ; 
 unsigned int PDC_20621_DIMM_DATA ; 
 int PDC_DIMM_APKT_PRD ; 
 unsigned int PDC_DIMM_DATA_STEP ; 
 unsigned int PDC_DIMM_WINDOW_STEP ; 
 int /*<<< orphan*/  VPRINTK (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static inline void pdc20621_ata_sg(u8 *buf, unsigned int portno,
				   unsigned int total_len)
{
	u32 addr;
	unsigned int dw = PDC_DIMM_APKT_PRD >> 2;
	__le32 *buf32 = (__le32 *) buf;

	/* output ATA packet S/G table */
	addr = PDC_20621_DIMM_BASE + PDC_20621_DIMM_DATA +
	       (PDC_DIMM_DATA_STEP * portno);
	VPRINTK("ATA sg addr 0x%x, %d\n", addr, addr);
	buf32[dw] = cpu_to_le32(addr);
	buf32[dw + 1] = cpu_to_le32(total_len | ATA_PRD_EOT);

	VPRINTK("ATA PSG @ %x == (0x%x, 0x%x)\n",
		PDC_20621_DIMM_BASE +
		       (PDC_DIMM_WINDOW_STEP * portno) +
		       PDC_DIMM_APKT_PRD,
		buf32[dw], buf32[dw + 1]);
}