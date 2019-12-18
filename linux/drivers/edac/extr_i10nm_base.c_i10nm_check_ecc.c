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
typedef  int /*<<< orphan*/  u32 ;
struct skx_imc {scalar_t__ mbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i10nm_check_ecc(struct skx_imc *imc, int chan)
{
	u32 mcmtr;

	mcmtr = *(u32 *)(imc->mbase + 0x20ef8 + chan * 0x4000);
	edac_dbg(1, "ch%d mcmtr reg %x\n", chan, mcmtr);

	return !!GET_BITFIELD(mcmtr, 2, 2);
}