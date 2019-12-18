#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct amd64_pvt {TYPE_1__* csels; } ;
struct TYPE_2__ {int* csmasks_sec; int* csmasks; } ;

/* Variables and functions */
 unsigned int CS_EVEN ; 
 unsigned int CS_ODD ; 
 unsigned int CS_ODD_SECONDARY ; 
 int GENMASK_ULL (int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,...) ; 
 int fls (int) ; 
 int hweight_long (int) ; 

__attribute__((used)) static int f17_addr_mask_to_cs_size(struct amd64_pvt *pvt, u8 umc,
				    unsigned int cs_mode, int csrow_nr)
{
	u32 addr_mask_orig, addr_mask_deinterleaved;
	u32 msb, weight, num_zero_bits;
	int dimm, size = 0;

	/* No Chip Selects are enabled. */
	if (!cs_mode)
		return size;

	/* Requested size of an even CS but none are enabled. */
	if (!(cs_mode & CS_EVEN) && !(csrow_nr & 1))
		return size;

	/* Requested size of an odd CS but none are enabled. */
	if (!(cs_mode & CS_ODD) && (csrow_nr & 1))
		return size;

	/*
	 * There is one mask per DIMM, and two Chip Selects per DIMM.
	 *	CS0 and CS1 -> DIMM0
	 *	CS2 and CS3 -> DIMM1
	 */
	dimm = csrow_nr >> 1;

	/* Asymmetric dual-rank DIMM support. */
	if ((csrow_nr & 1) && (cs_mode & CS_ODD_SECONDARY))
		addr_mask_orig = pvt->csels[umc].csmasks_sec[dimm];
	else
		addr_mask_orig = pvt->csels[umc].csmasks[dimm];

	/*
	 * The number of zero bits in the mask is equal to the number of bits
	 * in a full mask minus the number of bits in the current mask.
	 *
	 * The MSB is the number of bits in the full mask because BIT[0] is
	 * always 0.
	 */
	msb = fls(addr_mask_orig) - 1;
	weight = hweight_long(addr_mask_orig);
	num_zero_bits = msb - weight;

	/* Take the number of zero bits off from the top of the mask. */
	addr_mask_deinterleaved = GENMASK_ULL(msb - num_zero_bits, 1);

	edac_dbg(1, "CS%d DIMM%d AddrMasks:\n", csrow_nr, dimm);
	edac_dbg(1, "  Original AddrMask: 0x%x\n", addr_mask_orig);
	edac_dbg(1, "  Deinterleaved AddrMask: 0x%x\n", addr_mask_deinterleaved);

	/* Register [31:1] = Address [39:9]. Size is in kBs here. */
	size = (addr_mask_deinterleaved >> 2) + 1;

	/* Return size in MBs. */
	return size >> 10;
}