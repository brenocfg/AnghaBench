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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_restore ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  OPAL_REINIT_CPUS_HILE_BE ; 
 int /*<<< orphan*/  OPAL_REINIT_CPUS_HILE_LE ; 
 int /*<<< orphan*/  OPAL_REINIT_CPUS_MMU_HASH ; 
 int /*<<< orphan*/  OPAL_REINIT_CPUS_MMU_RADIX ; 
 TYPE_1__* cur_cpu_spec ; 
 scalar_t__ early_cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ early_radix_enabled () ; 
 int /*<<< orphan*/  opal_reinit_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void opal_configure_cores(void)
{
	u64 reinit_flags = 0;

	/* Do the actual re-init, This will clobber all FPRs, VRs, etc...
	 *
	 * It will preserve non volatile GPRs and HSPRG0/1. It will
	 * also restore HIDs and other SPRs to their original value
	 * but it might clobber a bunch.
	 */
#ifdef __BIG_ENDIAN__
	reinit_flags |= OPAL_REINIT_CPUS_HILE_BE;
#else
	reinit_flags |= OPAL_REINIT_CPUS_HILE_LE;
#endif

	/*
	 * POWER9 always support running hash:
	 *  ie. Host hash  supports  hash guests
	 *      Host radix supports  hash/radix guests
	 */
	if (early_cpu_has_feature(CPU_FTR_ARCH_300)) {
		reinit_flags |= OPAL_REINIT_CPUS_MMU_HASH;
		if (early_radix_enabled())
			reinit_flags |= OPAL_REINIT_CPUS_MMU_RADIX;
	}

	opal_reinit_cpus(reinit_flags);

	/* Restore some bits */
	if (cur_cpu_spec->cpu_restore)
		cur_cpu_spec->cpu_restore();
}