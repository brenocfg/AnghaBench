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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_FIREPLANE_CONFIG ; 
 int /*<<< orphan*/  AA_INTR_ID ; 
 int /*<<< orphan*/  ASI_FIREPLANE_CONFIG_REG ; 
 int /*<<< orphan*/  ASI_INTR_ID ; 
 int /*<<< orphan*/  ASI_JBUS_CONFIG_REG ; 
 int /*<<< orphan*/  ASI_UPA_CONFIG_REG ; 
#define  CPU_IMPL_SPARC64 139 
#define  CPU_IMPL_SPARC64V 138 
#define  CPU_IMPL_ULTRASPARCI 137 
#define  CPU_IMPL_ULTRASPARCII 136 
#define  CPU_IMPL_ULTRASPARCIII 135 
#define  CPU_IMPL_ULTRASPARCIIIi 134 
#define  CPU_IMPL_ULTRASPARCIIIip 133 
#define  CPU_IMPL_ULTRASPARCIIIp 132 
#define  CPU_IMPL_ULTRASPARCIIe 131 
#define  CPU_IMPL_ULTRASPARCIIi 130 
#define  CPU_IMPL_ULTRASPARCIV 129 
#define  CPU_IMPL_ULTRASPARCIVp 128 
 int /*<<< orphan*/  FIREPLANE_CR_GET_AID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTR_ID_GET_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JBUS_CR_GET_JID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPA_CR_GET_MID (int /*<<< orphan*/ ) ; 
 int cpu_impl ; 
 int /*<<< orphan*/  ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
cpu_get_mid_sun4u(void)
{

	switch (cpu_impl) {
	case CPU_IMPL_SPARC64:
	case CPU_IMPL_SPARC64V:
	case CPU_IMPL_ULTRASPARCI:
	case CPU_IMPL_ULTRASPARCII:
	case CPU_IMPL_ULTRASPARCIIi:
	case CPU_IMPL_ULTRASPARCIIe:
		return (UPA_CR_GET_MID(ldxa(0, ASI_UPA_CONFIG_REG)));
	case CPU_IMPL_ULTRASPARCIII:
	case CPU_IMPL_ULTRASPARCIIIp:
		return (FIREPLANE_CR_GET_AID(ldxa(AA_FIREPLANE_CONFIG,
		    ASI_FIREPLANE_CONFIG_REG)));
	case CPU_IMPL_ULTRASPARCIIIi:
	case CPU_IMPL_ULTRASPARCIIIip:
		return (JBUS_CR_GET_JID(ldxa(0, ASI_JBUS_CONFIG_REG)));
	case CPU_IMPL_ULTRASPARCIV:
	case CPU_IMPL_ULTRASPARCIVp:
		return (INTR_ID_GET_ID(ldxa(AA_INTR_ID, ASI_INTR_ID)));
	default:
		return (0);
	}
}