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
typedef  int u_int ;

/* Variables and functions */
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

const char *
cpu_portid_prop(u_int cpu_impl)
{

	switch (cpu_impl) {
	case CPU_IMPL_SPARC64:
	case CPU_IMPL_SPARC64V:
	case CPU_IMPL_ULTRASPARCI:
	case CPU_IMPL_ULTRASPARCII:
	case CPU_IMPL_ULTRASPARCIIi:
	case CPU_IMPL_ULTRASPARCIIe:
		return ("upa-portid");
	case CPU_IMPL_ULTRASPARCIII:
	case CPU_IMPL_ULTRASPARCIIIp:
	case CPU_IMPL_ULTRASPARCIIIi:
	case CPU_IMPL_ULTRASPARCIIIip:
		return ("portid");
	case CPU_IMPL_ULTRASPARCIV:
	case CPU_IMPL_ULTRASPARCIVp:
		return ("cpuid");
	default:
		return ("");
	}
}