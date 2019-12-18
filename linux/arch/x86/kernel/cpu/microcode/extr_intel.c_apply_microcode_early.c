#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ rev; } ;
struct ucode_cpu_info {TYPE_2__ cpu_sig; struct microcode_intel* mc; } ;
struct TYPE_3__ {scalar_t__ rev; int /*<<< orphan*/  date; } ;
struct microcode_intel {TYPE_1__ hdr; scalar_t__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_UCODE_WRITE ; 
 int UCODE_OK ; 
 scalar_t__ intel_get_microcode_revision () ; 
 int /*<<< orphan*/  native_wbinvd () ; 
 int /*<<< orphan*/  native_wrmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  print_ucode (struct ucode_cpu_info*) ; 
 int /*<<< orphan*/  print_ucode_info (struct ucode_cpu_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_microcode_early(struct ucode_cpu_info *uci, bool early)
{
	struct microcode_intel *mc;
	u32 rev;

	mc = uci->mc;
	if (!mc)
		return 0;

	/*
	 * Save us the MSR write below - which is a particular expensive
	 * operation - when the other hyperthread has updated the microcode
	 * already.
	 */
	rev = intel_get_microcode_revision();
	if (rev >= mc->hdr.rev) {
		uci->cpu_sig.rev = rev;
		return UCODE_OK;
	}

	/*
	 * Writeback and invalidate caches before updating microcode to avoid
	 * internal issues depending on what the microcode is updating.
	 */
	native_wbinvd();

	/* write microcode via MSR 0x79 */
	native_wrmsrl(MSR_IA32_UCODE_WRITE, (unsigned long)mc->bits);

	rev = intel_get_microcode_revision();
	if (rev != mc->hdr.rev)
		return -1;

	uci->cpu_sig.rev = rev;

	if (early)
		print_ucode(uci);
	else
		print_ucode_info(uci, mc->hdr.date);

	return 0;
}