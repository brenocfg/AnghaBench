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
typedef  enum sysdecode_abi { ____Placeholder_sysdecode_abi } sysdecode_abi ;

/* Variables and functions */
 int INT_MAX ; 
#define  SYSDECODE_ABI_CLOUDABI32 133 
#define  SYSDECODE_ABI_CLOUDABI64 132 
#define  SYSDECODE_ABI_FREEBSD 131 
#define  SYSDECODE_ABI_FREEBSD32 130 
#define  SYSDECODE_ABI_LINUX 129 
#define  SYSDECODE_ABI_LINUX32 128 
 int* cloudabi_errno_table ; 
 int* linux_errtbl ; 
 unsigned int nitems (int*) ; 

int
sysdecode_abi_to_freebsd_errno(enum sysdecode_abi abi, int error)
{

	switch (abi) {
	case SYSDECODE_ABI_FREEBSD:
	case SYSDECODE_ABI_FREEBSD32:
		return (error);
#if defined(__aarch64__) || defined(__amd64__) || defined(__i386__)
	case SYSDECODE_ABI_LINUX:
	case SYSDECODE_ABI_LINUX32: {
		unsigned int i;

		/*
		 * This is imprecise since it returns the first
		 * matching errno.
		 */
		for (i = 0; i < nitems(linux_errtbl); i++) {
			if (error == linux_errtbl[i])
				return (i);
		}
		break;
	}
#endif
	case SYSDECODE_ABI_CLOUDABI32:
	case SYSDECODE_ABI_CLOUDABI64:
		if (error >= 0 &&
		    (unsigned int)error < nitems(cloudabi_errno_table))
			return (cloudabi_errno_table[error]);
		break;
	default:
		break;
	}
	return (INT_MAX);
}