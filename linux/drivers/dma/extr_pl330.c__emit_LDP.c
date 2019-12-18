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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  enum pl330_cond { ____Placeholder_pl330_cond } pl330_cond ;

/* Variables and functions */
 int BURST ; 
 int CMD_DMALDP ; 
 int /*<<< orphan*/  PL330_DBGCMD_DUMP (int /*<<< orphan*/ ,char*,char,int) ; 
 int SINGLE ; 
 int /*<<< orphan*/  SZ_DMALDP ; 

__attribute__((used)) static inline u32 _emit_LDP(unsigned dry_run, u8 buf[],
		enum pl330_cond cond, u8 peri)
{
	if (dry_run)
		return SZ_DMALDP;

	buf[0] = CMD_DMALDP;

	if (cond == BURST)
		buf[0] |= (1 << 1);

	peri &= 0x1f;
	peri <<= 3;
	buf[1] = peri;

	PL330_DBGCMD_DUMP(SZ_DMALDP, "\tDMALDP%c %u\n",
		cond == SINGLE ? 'S' : 'B', peri >> 3);

	return SZ_DMALDP;
}