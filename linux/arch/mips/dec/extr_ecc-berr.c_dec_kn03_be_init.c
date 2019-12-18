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

/* Variables and functions */
 scalar_t__ CKSEG1ADDR (scalar_t__) ; 
 scalar_t__ CPU_R4400SC ; 
 scalar_t__ IOASIC_CHKSYN ; 
 scalar_t__ IOASIC_ERRADDR ; 
 scalar_t__ IOASIC_MCR ; 
 int volatile KN03_MCR_CORRECT ; 
 int volatile KN03_MCR_DIAGCHK ; 
 int volatile KN03_MCR_DIAGGEN ; 
 scalar_t__ KN03_SLOT_BASE ; 
 scalar_t__ KN4K_MB_CSR ; 
 int volatile KN4K_MB_CSR_EE ; 
 scalar_t__ KN4K_SLOT_BASE ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  fast_iob () ; 
 void* kn0x_chksyn ; 
 void* kn0x_erraddr ; 

__attribute__((used)) static inline void dec_kn03_be_init(void)
{
	volatile u32 *mcr = (void *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_MCR);
	volatile u32 *mbcs = (void *)CKSEG1ADDR(KN4K_SLOT_BASE + KN4K_MB_CSR);

	kn0x_erraddr = (void *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_ERRADDR);
	kn0x_chksyn = (void *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_CHKSYN);

	/*
	 * Set normal ECC detection and generation, enable ECC correction.
	 * For KN05 we also need to make sure EE (?) is enabled in the MB.
	 * Otherwise DBE/IBE exceptions would be masked but bus error
	 * interrupts would still arrive, resulting in an inevitable crash
	 * if get_dbe() triggers one.
	 */
	*mcr = (*mcr & ~(KN03_MCR_DIAGCHK | KN03_MCR_DIAGGEN)) |
	       KN03_MCR_CORRECT;
	if (current_cpu_type() == CPU_R4400SC)
		*mbcs |= KN4K_MB_CSR_EE;
	fast_iob();
}