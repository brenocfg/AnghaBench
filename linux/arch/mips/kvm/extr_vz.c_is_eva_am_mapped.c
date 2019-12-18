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
union mips_instruction {int /*<<< orphan*/  word; } ;
typedef  int u32 ;
struct TYPE_2__ {int host_cp0_cause; scalar_t__ pc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CAUSEF_BD ; 
 unsigned int ST0_ERL ; 
 unsigned int ST0_EXL ; 
 unsigned int ST0_KSU ; 
 scalar_t__ is_eva_access (union mips_instruction) ; 
 int kvm_get_badinstr (int*,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 unsigned int read_gc0_status () ; 

__attribute__((used)) static bool is_eva_am_mapped(struct kvm_vcpu *vcpu, unsigned int am, bool eu)
{
	u32 am_lookup;
	int err;

	/*
	 * Interpret access control mode. We assume address errors will already
	 * have been caught by the guest, leaving us with:
	 *      AM      UM  SM  KM  31..24 23..16
	 * UK    0 000          Unm   0      0
	 * MK    1 001          TLB   1
	 * MSK   2 010      TLB TLB   1
	 * MUSK  3 011  TLB TLB TLB   1
	 * MUSUK 4 100  TLB TLB Unm   0      1
	 * USK   5 101      Unm Unm   0      0
	 * -     6 110                0      0
	 * UUSK  7 111  Unm Unm Unm   0      0
	 *
	 * We shift a magic value by AM across the sign bit to find if always
	 * TLB mapped, and if not shift by 8 again to find if it depends on KM.
	 */
	am_lookup = 0x70080000 << am;
	if ((s32)am_lookup < 0) {
		/*
		 * MK, MSK, MUSK
		 * Always TLB mapped, unless SegCtl.EU && ERL
		 */
		if (!eu || !(read_gc0_status() & ST0_ERL))
			return true;
	} else {
		am_lookup <<= 8;
		if ((s32)am_lookup < 0) {
			union mips_instruction inst;
			unsigned int status;
			u32 *opc;

			/*
			 * MUSUK
			 * TLB mapped if not in kernel mode
			 */
			status = read_gc0_status();
			if (!(status & (ST0_EXL | ST0_ERL)) &&
			    (status & ST0_KSU))
				return true;
			/*
			 * EVA access instructions in kernel
			 * mode access user address space.
			 */
			opc = (u32 *)vcpu->arch.pc;
			if (vcpu->arch.host_cp0_cause & CAUSEF_BD)
				opc += 1;
			err = kvm_get_badinstr(opc, vcpu, &inst.word);
			if (!err && is_eva_access(inst))
				return true;
		}
	}

	return false;
}