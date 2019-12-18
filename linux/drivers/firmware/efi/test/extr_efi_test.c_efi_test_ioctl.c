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
struct file {int dummy; } ;

/* Variables and functions */
#define  EFI_RUNTIME_GET_NEXTHIGHMONOTONICCOUNT 138 
#define  EFI_RUNTIME_GET_NEXTVARIABLENAME 137 
#define  EFI_RUNTIME_GET_TIME 136 
#define  EFI_RUNTIME_GET_VARIABLE 135 
#define  EFI_RUNTIME_GET_WAKETIME 134 
#define  EFI_RUNTIME_QUERY_CAPSULECAPABILITIES 133 
#define  EFI_RUNTIME_QUERY_VARIABLEINFO 132 
#define  EFI_RUNTIME_RESET_SYSTEM 131 
#define  EFI_RUNTIME_SET_TIME 130 
#define  EFI_RUNTIME_SET_VARIABLE 129 
#define  EFI_RUNTIME_SET_WAKETIME 128 
 long ENOTTY ; 
 long efi_runtime_get_nexthighmonocount (unsigned long) ; 
 long efi_runtime_get_nextvariablename (unsigned long) ; 
 long efi_runtime_get_time (unsigned long) ; 
 long efi_runtime_get_variable (unsigned long) ; 
 long efi_runtime_get_waketime (unsigned long) ; 
 long efi_runtime_query_capsulecaps (unsigned long) ; 
 long efi_runtime_query_variableinfo (unsigned long) ; 
 long efi_runtime_reset_system (unsigned long) ; 
 long efi_runtime_set_time (unsigned long) ; 
 long efi_runtime_set_variable (unsigned long) ; 
 long efi_runtime_set_waketime (unsigned long) ; 

__attribute__((used)) static long efi_test_ioctl(struct file *file, unsigned int cmd,
							unsigned long arg)
{
	switch (cmd) {
	case EFI_RUNTIME_GET_VARIABLE:
		return efi_runtime_get_variable(arg);

	case EFI_RUNTIME_SET_VARIABLE:
		return efi_runtime_set_variable(arg);

	case EFI_RUNTIME_GET_TIME:
		return efi_runtime_get_time(arg);

	case EFI_RUNTIME_SET_TIME:
		return efi_runtime_set_time(arg);

	case EFI_RUNTIME_GET_WAKETIME:
		return efi_runtime_get_waketime(arg);

	case EFI_RUNTIME_SET_WAKETIME:
		return efi_runtime_set_waketime(arg);

	case EFI_RUNTIME_GET_NEXTVARIABLENAME:
		return efi_runtime_get_nextvariablename(arg);

	case EFI_RUNTIME_GET_NEXTHIGHMONOTONICCOUNT:
		return efi_runtime_get_nexthighmonocount(arg);

	case EFI_RUNTIME_QUERY_VARIABLEINFO:
		return efi_runtime_query_variableinfo(arg);

	case EFI_RUNTIME_QUERY_CAPSULECAPABILITIES:
		return efi_runtime_query_capsulecaps(arg);

	case EFI_RUNTIME_RESET_SYSTEM:
		return efi_runtime_reset_system(arg);
	}

	return -ENOTTY;
}