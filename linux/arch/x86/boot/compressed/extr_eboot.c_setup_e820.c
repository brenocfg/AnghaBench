#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct setup_data {scalar_t__ data; } ;
struct efi_info {int efi_memmap_size; int efi_memdesc_size; unsigned long efi_memmap; scalar_t__ efi_memmap_hi; } ;
struct e820_entry {int dummy; } ;
struct boot_params {scalar_t__ e820_entries; struct boot_e820_entry* e820_table; struct efi_info efi_info; } ;
struct boot_e820_entry {unsigned int type; scalar_t__ addr; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  efi_status_t ;
struct TYPE_3__ {int type; scalar_t__ phys_addr; int num_pages; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct boot_e820_entry*) ; 
 unsigned int E820_TYPE_ACPI ; 
 unsigned int E820_TYPE_NVS ; 
 unsigned int E820_TYPE_PMEM ; 
 unsigned int E820_TYPE_RAM ; 
 unsigned int E820_TYPE_RESERVED ; 
 unsigned int E820_TYPE_UNUSABLE ; 
#define  EFI_ACPI_MEMORY_NVS 142 
#define  EFI_ACPI_RECLAIM_MEMORY 141 
#define  EFI_BOOT_SERVICES_CODE 140 
#define  EFI_BOOT_SERVICES_DATA 139 
 int /*<<< orphan*/  EFI_BUFFER_TOO_SMALL ; 
#define  EFI_CONVENTIONAL_MEMORY 138 
#define  EFI_LOADER_CODE 137 
#define  EFI_LOADER_DATA 136 
#define  EFI_MEMORY_MAPPED_IO 135 
#define  EFI_MEMORY_MAPPED_IO_PORT_SPACE 134 
#define  EFI_PAL_CODE 133 
#define  EFI_PERSISTENT_MEMORY 132 
#define  EFI_RESERVED_TYPE 131 
#define  EFI_RUNTIME_SERVICES_CODE 130 
#define  EFI_RUNTIME_SERVICES_DATA 129 
 int /*<<< orphan*/  EFI_SUCCESS ; 
#define  EFI_UNUSABLE_MEMORY 128 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  add_e820ext (struct boot_params*,struct setup_data*,int) ; 
 TYPE_1__* efi_early_memdesc_ptr (unsigned long,int,int) ; 

__attribute__((used)) static efi_status_t
setup_e820(struct boot_params *params, struct setup_data *e820ext, u32 e820ext_size)
{
	struct boot_e820_entry *entry = params->e820_table;
	struct efi_info *efi = &params->efi_info;
	struct boot_e820_entry *prev = NULL;
	u32 nr_entries;
	u32 nr_desc;
	int i;

	nr_entries = 0;
	nr_desc = efi->efi_memmap_size / efi->efi_memdesc_size;

	for (i = 0; i < nr_desc; i++) {
		efi_memory_desc_t *d;
		unsigned int e820_type = 0;
		unsigned long m = efi->efi_memmap;

#ifdef CONFIG_X86_64
		m |= (u64)efi->efi_memmap_hi << 32;
#endif

		d = efi_early_memdesc_ptr(m, efi->efi_memdesc_size, i);
		switch (d->type) {
		case EFI_RESERVED_TYPE:
		case EFI_RUNTIME_SERVICES_CODE:
		case EFI_RUNTIME_SERVICES_DATA:
		case EFI_MEMORY_MAPPED_IO:
		case EFI_MEMORY_MAPPED_IO_PORT_SPACE:
		case EFI_PAL_CODE:
			e820_type = E820_TYPE_RESERVED;
			break;

		case EFI_UNUSABLE_MEMORY:
			e820_type = E820_TYPE_UNUSABLE;
			break;

		case EFI_ACPI_RECLAIM_MEMORY:
			e820_type = E820_TYPE_ACPI;
			break;

		case EFI_LOADER_CODE:
		case EFI_LOADER_DATA:
		case EFI_BOOT_SERVICES_CODE:
		case EFI_BOOT_SERVICES_DATA:
		case EFI_CONVENTIONAL_MEMORY:
			e820_type = E820_TYPE_RAM;
			break;

		case EFI_ACPI_MEMORY_NVS:
			e820_type = E820_TYPE_NVS;
			break;

		case EFI_PERSISTENT_MEMORY:
			e820_type = E820_TYPE_PMEM;
			break;

		default:
			continue;
		}

		/* Merge adjacent mappings */
		if (prev && prev->type == e820_type &&
		    (prev->addr + prev->size) == d->phys_addr) {
			prev->size += d->num_pages << 12;
			continue;
		}

		if (nr_entries == ARRAY_SIZE(params->e820_table)) {
			u32 need = (nr_desc - i) * sizeof(struct e820_entry) +
				   sizeof(struct setup_data);

			if (!e820ext || e820ext_size < need)
				return EFI_BUFFER_TOO_SMALL;

			/* boot_params map full, switch to e820 extended */
			entry = (struct boot_e820_entry *)e820ext->data;
		}

		entry->addr = d->phys_addr;
		entry->size = d->num_pages << PAGE_SHIFT;
		entry->type = e820_type;
		prev = entry++;
		nr_entries++;
	}

	if (nr_entries > ARRAY_SIZE(params->e820_table)) {
		u32 nr_e820ext = nr_entries - ARRAY_SIZE(params->e820_table);

		add_e820ext(params, e820ext, nr_e820ext);
		nr_entries -= nr_e820ext;
	}

	params->e820_entries = (u8)nr_entries;

	return EFI_SUCCESS;
}