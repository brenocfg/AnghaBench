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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct efi_md {size_t md_type; int md_attr; scalar_t__ md_pages; int /*<<< orphan*/  md_virt; scalar_t__ md_phys; } ;
struct efi_map_header {int descriptor_size; size_t memory_size; } ;

/* Variables and functions */
 int EFI_MD_ATTR_RP ; 
 int EFI_MD_ATTR_RT ; 
 int EFI_MD_ATTR_UC ; 
 int EFI_MD_ATTR_UCE ; 
 int EFI_MD_ATTR_WB ; 
 int EFI_MD_ATTR_WC ; 
 int EFI_MD_ATTR_WP ; 
 int EFI_MD_ATTR_WT ; 
 int EFI_MD_ATTR_XP ; 
#define  EFI_MD_TYPE_BAD 142 
#define  EFI_MD_TYPE_BS_CODE 141 
#define  EFI_MD_TYPE_BS_DATA 140 
#define  EFI_MD_TYPE_CODE 139 
#define  EFI_MD_TYPE_DATA 138 
#define  EFI_MD_TYPE_FIRMWARE 137 
#define  EFI_MD_TYPE_FREE 136 
#define  EFI_MD_TYPE_IOMEM 135 
#define  EFI_MD_TYPE_IOPORT 134 
#define  EFI_MD_TYPE_NULL 133 
#define  EFI_MD_TYPE_PALCODE 132 
#define  EFI_MD_TYPE_PERSISTENT 131 
#define  EFI_MD_TYPE_RECLAIM 130 
#define  EFI_MD_TYPE_RT_CODE 129 
#define  EFI_MD_TYPE_RT_DATA 128 
 struct efi_md* efi_next_descriptor (struct efi_md*,int) ; 
 size_t nitems (char const* const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
S_efi_map(size_t l2, void *p)
{
	struct efi_map_header *efihdr;
	struct efi_md *map;
	const char *type;
	size_t efisz;
	int ndesc, i;

	static const char * const types[] = {
		[EFI_MD_TYPE_NULL] =	"Reserved",
		[EFI_MD_TYPE_CODE] =	"LoaderCode",
		[EFI_MD_TYPE_DATA] =	"LoaderData",
		[EFI_MD_TYPE_BS_CODE] =	"BootServicesCode",
		[EFI_MD_TYPE_BS_DATA] =	"BootServicesData",
		[EFI_MD_TYPE_RT_CODE] =	"RuntimeServicesCode",
		[EFI_MD_TYPE_RT_DATA] =	"RuntimeServicesData",
		[EFI_MD_TYPE_FREE] =	"ConventionalMemory",
		[EFI_MD_TYPE_BAD] =	"UnusableMemory",
		[EFI_MD_TYPE_RECLAIM] =	"ACPIReclaimMemory",
		[EFI_MD_TYPE_FIRMWARE] = "ACPIMemoryNVS",
		[EFI_MD_TYPE_IOMEM] =	"MemoryMappedIO",
		[EFI_MD_TYPE_IOPORT] =	"MemoryMappedIOPortSpace",
		[EFI_MD_TYPE_PALCODE] =	"PalCode",
		[EFI_MD_TYPE_PERSISTENT] = "PersistentMemory",
	};

	/*
	 * Memory map data provided by UEFI via the GetMemoryMap
	 * Boot Services API.
	 */
	if (l2 < sizeof(*efihdr)) {
		warnx("S_efi_map length less than header");
		return (1);
	}
	efihdr = p;
	efisz = (sizeof(struct efi_map_header) + 0xf) & ~0xf;
	map = (struct efi_md *)((uint8_t *)efihdr + efisz);

	if (efihdr->descriptor_size == 0)
		return (0);
	if (l2 != efisz + efihdr->memory_size) {
		warnx("S_efi_map length mismatch %zu vs %zu", l2, efisz +
		    efihdr->memory_size);
		return (1);
	}
	ndesc = efihdr->memory_size / efihdr->descriptor_size;

	printf("\n%23s %12s %12s %8s %4s",
	    "Type", "Physical", "Virtual", "#Pages", "Attr");

	for (i = 0; i < ndesc; i++,
	    map = efi_next_descriptor(map, efihdr->descriptor_size)) {
		type = NULL;
		if (map->md_type < nitems(types))
			type = types[map->md_type];
		if (type == NULL)
			type = "<INVALID>";
		printf("\n%23s %012jx %12p %08jx ", type,
		    (uintmax_t)map->md_phys, map->md_virt,
		    (uintmax_t)map->md_pages);
		if (map->md_attr & EFI_MD_ATTR_UC)
			printf("UC ");
		if (map->md_attr & EFI_MD_ATTR_WC)
			printf("WC ");
		if (map->md_attr & EFI_MD_ATTR_WT)
			printf("WT ");
		if (map->md_attr & EFI_MD_ATTR_WB)
			printf("WB ");
		if (map->md_attr & EFI_MD_ATTR_UCE)
			printf("UCE ");
		if (map->md_attr & EFI_MD_ATTR_WP)
			printf("WP ");
		if (map->md_attr & EFI_MD_ATTR_RP)
			printf("RP ");
		if (map->md_attr & EFI_MD_ATTR_XP)
			printf("XP ");
		if (map->md_attr & EFI_MD_ATTR_RT)
			printf("RUNTIME");
	}
	return (0);
}