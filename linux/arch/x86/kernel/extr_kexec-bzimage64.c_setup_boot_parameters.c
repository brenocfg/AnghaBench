#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct screen_info {int dummy; } ;
struct kimage {scalar_t__ type; } ;
struct edd_info {int dummy; } ;
struct TYPE_9__ {unsigned long long ext_mem_k; } ;
struct TYPE_6__ {int /*<<< orphan*/  hardware_subarch; } ;
struct boot_params {unsigned long long alt_mem_k; unsigned int e820_entries; TYPE_4__* edd_mbr_sig_buffer; int /*<<< orphan*/  eddbuf_entries; TYPE_4__* eddbuf; TYPE_4__ screen_info; TYPE_3__* e820_table; int /*<<< orphan*/  hd1_info; int /*<<< orphan*/  hd0_info; int /*<<< orphan*/  apm_bios_info; int /*<<< orphan*/  acpi_rsdp_addr; TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  hardware_subarch; } ;
struct TYPE_10__ {int /*<<< orphan*/ * edd_mbr_sig_buffer; int /*<<< orphan*/  eddbuf_entries; int /*<<< orphan*/ * eddbuf; int /*<<< orphan*/  acpi_rsdp_addr; int /*<<< orphan*/  screen_info; TYPE_2__ hdr; } ;
struct TYPE_8__ {scalar_t__ type; unsigned long long addr; int size; } ;

/* Variables and functions */
 scalar_t__ E820_TYPE_RAM ; 
 int EDDMAXNR ; 
 int EDD_MBR_SIG_MAX ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 TYPE_5__ boot_params ; 
 int crash_setup_memmap_entries (struct kimage*,struct boot_params*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_e820_entries (struct boot_params*) ; 
 int /*<<< orphan*/  setup_efi_state (struct boot_params*,unsigned long,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
setup_boot_parameters(struct kimage *image, struct boot_params *params,
		      unsigned long params_load_addr,
		      unsigned int efi_map_offset, unsigned int efi_map_sz,
		      unsigned int efi_setup_data_offset)
{
	unsigned int nr_e820_entries;
	unsigned long long mem_k, start, end;
	int i, ret = 0;

	/* Get subarch from existing bootparams */
	params->hdr.hardware_subarch = boot_params.hdr.hardware_subarch;

	/* Copying screen_info will do? */
	memcpy(&params->screen_info, &boot_params.screen_info,
				sizeof(struct screen_info));

	/* Fill in memsize later */
	params->screen_info.ext_mem_k = 0;
	params->alt_mem_k = 0;

	/* Always fill in RSDP: it is either 0 or a valid value */
	params->acpi_rsdp_addr = boot_params.acpi_rsdp_addr;

	/* Default APM info */
	memset(&params->apm_bios_info, 0, sizeof(params->apm_bios_info));

	/* Default drive info */
	memset(&params->hd0_info, 0, sizeof(params->hd0_info));
	memset(&params->hd1_info, 0, sizeof(params->hd1_info));

	if (image->type == KEXEC_TYPE_CRASH) {
		ret = crash_setup_memmap_entries(image, params);
		if (ret)
			return ret;
	} else
		setup_e820_entries(params);

	nr_e820_entries = params->e820_entries;

	for (i = 0; i < nr_e820_entries; i++) {
		if (params->e820_table[i].type != E820_TYPE_RAM)
			continue;
		start = params->e820_table[i].addr;
		end = params->e820_table[i].addr + params->e820_table[i].size - 1;

		if ((start <= 0x100000) && end > 0x100000) {
			mem_k = (end >> 10) - (0x100000 >> 10);
			params->screen_info.ext_mem_k = mem_k;
			params->alt_mem_k = mem_k;
			if (mem_k > 0xfc00)
				params->screen_info.ext_mem_k = 0xfc00; /* 64M*/
			if (mem_k > 0xffffffff)
				params->alt_mem_k = 0xffffffff;
		}
	}

#ifdef CONFIG_EFI
	/* Setup EFI state */
	setup_efi_state(params, params_load_addr, efi_map_offset, efi_map_sz,
			efi_setup_data_offset);
#endif
	/* Setup EDD info */
	memcpy(params->eddbuf, boot_params.eddbuf,
				EDDMAXNR * sizeof(struct edd_info));
	params->eddbuf_entries = boot_params.eddbuf_entries;

	memcpy(params->edd_mbr_sig_buffer, boot_params.edd_mbr_sig_buffer,
	       EDD_MBR_SIG_MAX * sizeof(unsigned int));

	return ret;
}