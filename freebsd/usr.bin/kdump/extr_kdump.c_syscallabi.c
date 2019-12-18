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
typedef  enum sysdecode_abi { ____Placeholder_sysdecode_abi } sysdecode_abi ;

/* Variables and functions */
#define  SV_ABI_CLOUDABI 130 
#define  SV_ABI_FREEBSD 129 
#define  SV_ABI_LINUX 128 
 int SV_ABI_MASK ; 
 int SV_ILP32 ; 
 int SYSDECODE_ABI_CLOUDABI64 ; 
 int SYSDECODE_ABI_FREEBSD ; 
 int SYSDECODE_ABI_LINUX ; 
 int SYSDECODE_ABI_LINUX32 ; 
 int SYSDECODE_ABI_UNKNOWN ; 

__attribute__((used)) static enum sysdecode_abi
syscallabi(u_int sv_flags)
{

	if (sv_flags == 0)
		return (SYSDECODE_ABI_FREEBSD);
	switch (sv_flags & SV_ABI_MASK) {
	case SV_ABI_FREEBSD:
		return (SYSDECODE_ABI_FREEBSD);
	case SV_ABI_LINUX:
#ifdef __LP64__
		if (sv_flags & SV_ILP32)
			return (SYSDECODE_ABI_LINUX32);
#endif
		return (SYSDECODE_ABI_LINUX);
	case SV_ABI_CLOUDABI:
		return (SYSDECODE_ABI_CLOUDABI64);
	default:
		return (SYSDECODE_ABI_UNKNOWN);
	}
}