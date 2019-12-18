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

/* Variables and functions */
 int BQ_DISTRUST_E820_EXTMEM ; 
 int B_BASEMEM_12 ; 
 int B_BASEMEM_E820 ; 
 int B_EXTMEM_8800 ; 
 int B_EXTMEM_E801 ; 
 int B_EXTMEM_E820 ; 
 int CMD_OK ; 
 int b_bios_probed ; 
 scalar_t__ bios_basemem ; 
 scalar_t__ bios_extmem ; 
 int bios_getquirks () ; 
 scalar_t__ high_heap_base ; 
 scalar_t__ high_heap_size ; 
 scalar_t__ memtop ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
command_biosmem(int argc, char *argv[])
{
	int bq = bios_getquirks();

	printf("bios_basemem: 0x%llx\n", (unsigned long long)bios_basemem);
	printf("bios_extmem: 0x%llx\n", (unsigned long long)bios_extmem);
	printf("memtop: 0x%llx\n", (unsigned long long)memtop);
	printf("high_heap_base: 0x%llx\n", (unsigned long long)high_heap_base);
	printf("high_heap_size: 0x%llx\n", (unsigned long long)high_heap_size);
	printf("bios_quirks: 0x%02x", bq);
	if (bq & BQ_DISTRUST_E820_EXTMEM)
		printf(" BQ_DISTRUST_E820_EXTMEM");
	printf("\n");
	printf("b_bios_probed: 0x%02x", (int)b_bios_probed);
	if (b_bios_probed & B_BASEMEM_E820)
		printf(" B_BASEMEM_E820");
	if (b_bios_probed & B_BASEMEM_12)
		printf(" B_BASEMEM_12");
	if (b_bios_probed & B_EXTMEM_E820)
		printf(" B_EXTMEM_E820");
	if (b_bios_probed & B_EXTMEM_E801)
		printf(" B_EXTMEM_E801");
	if (b_bios_probed & B_EXTMEM_8800)
		printf(" B_EXTMEM_8800");
	printf("\n");

	return (CMD_OK);
}