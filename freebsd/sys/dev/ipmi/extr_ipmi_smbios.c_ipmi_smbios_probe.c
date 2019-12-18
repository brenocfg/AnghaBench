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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ u_int32_t ;
struct smbios_eps {int length; scalar_t__ structure_table_address; int structure_table_length; int /*<<< orphan*/  number_structures; } ;
struct ipmi_get_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBIOS_LEN ; 
 int /*<<< orphan*/  SMBIOS_OFF ; 
 int /*<<< orphan*/  SMBIOS_SIG ; 
 int /*<<< orphan*/  SMBIOS_START ; 
 int /*<<< orphan*/  SMBIOS_STEP ; 
 scalar_t__ bios_sigsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ipmi_get_info*,int) ; 
 void* pmap_mapbios (scalar_t__,int) ; 
 int /*<<< orphan*/  pmap_unmapbios (int /*<<< orphan*/ ,int) ; 
 scalar_t__ smbios_cksum (struct smbios_eps*) ; 
 int /*<<< orphan*/  smbios_ipmi_info ; 
 int /*<<< orphan*/  smbios_walk_table (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipmi_get_info*) ; 

__attribute__((used)) static void
ipmi_smbios_probe(struct ipmi_get_info *info)
{
	struct smbios_eps *header;
	void *table;
	u_int32_t addr;

	bzero(info, sizeof(struct ipmi_get_info));

	/* Find the SMBIOS table header. */
	addr = bios_sigsearch(SMBIOS_START, SMBIOS_SIG, SMBIOS_LEN,
			      SMBIOS_STEP, SMBIOS_OFF);
	if (addr == 0)
		return;

	/*
	 * Map the header.  We first map a fixed size to get the actual
	 * length and then map it a second time with the actual length so
	 * we can verify the checksum.
	 */
	header = pmap_mapbios(addr, sizeof(struct smbios_eps));
	table = pmap_mapbios(addr, header->length);
	pmap_unmapbios((vm_offset_t)header, sizeof(struct smbios_eps));
	header = table;
	if (smbios_cksum(header) != 0) {
		pmap_unmapbios((vm_offset_t)header, header->length);
		return;
	}

	/* Now map the actual table and walk it looking for an IPMI entry. */
	table = pmap_mapbios(header->structure_table_address,
	    header->structure_table_length);
	smbios_walk_table(table, header->number_structures, smbios_ipmi_info,
	    info);

	/* Unmap everything. */
	pmap_unmapbios((vm_offset_t)table, header->structure_table_length);
	pmap_unmapbios((vm_offset_t)header, header->length);
}