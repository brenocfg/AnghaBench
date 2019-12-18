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
typedef  int EFI_MEMORY_TYPE ;

/* Variables and functions */
#define  EfiACPIMemoryNVS 142 
#define  EfiACPIReclaimMemory 141 
#define  EfiBootServicesCode 140 
#define  EfiBootServicesData 139 
#define  EfiConventionalMemory 138 
#define  EfiLoaderCode 137 
#define  EfiLoaderData 136 
#define  EfiMemoryMappedIO 135 
#define  EfiMemoryMappedIOPortSpace 134 
#define  EfiPalCode 133 
#define  EfiPersistentMemory 132 
#define  EfiReservedMemoryType 131 
#define  EfiRuntimeServicesCode 130 
#define  EfiRuntimeServicesData 129 
#define  EfiUnusableMemory 128 

const char *
efi_memory_type(EFI_MEMORY_TYPE type)
{
	const char *types[] = {
	    "Reserved",
	    "LoaderCode",
	    "LoaderData",
	    "BootServicesCode",
	    "BootServicesData",
	    "RuntimeServicesCode",
	    "RuntimeServicesData",
	    "ConventionalMemory",
	    "UnusableMemory",
	    "ACPIReclaimMemory",
	    "ACPIMemoryNVS",
	    "MemoryMappedIO",
	    "MemoryMappedIOPortSpace",
	    "PalCode",
	    "PersistentMemory"
	};

	switch (type) {
	case EfiReservedMemoryType:
	case EfiLoaderCode:
	case EfiLoaderData:
	case EfiBootServicesCode:
	case EfiBootServicesData:
	case EfiRuntimeServicesCode:
	case EfiRuntimeServicesData:
	case EfiConventionalMemory:
	case EfiUnusableMemory:
	case EfiACPIReclaimMemory:
	case EfiACPIMemoryNVS:
	case EfiMemoryMappedIO:
	case EfiMemoryMappedIOPortSpace:
	case EfiPalCode:
	case EfiPersistentMemory:
		return (types[type]);
	default:
		return ("Unknown");
	}
}