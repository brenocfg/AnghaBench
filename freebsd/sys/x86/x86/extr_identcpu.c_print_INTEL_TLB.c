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
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TO_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_INTEL_TLB(u_int data)
{
	switch (data) {
	case 0x0:
	case 0x40:
	default:
		break;
	case 0x1:
		printf("Instruction TLB: 4 KB pages, 4-way set associative, 32 entries\n");
		break;
	case 0x2:
		printf("Instruction TLB: 4 MB pages, fully associative, 2 entries\n");
		break;
	case 0x3:
		printf("Data TLB: 4 KB pages, 4-way set associative, 64 entries\n");
		break;
	case 0x4:
		printf("Data TLB: 4 MB Pages, 4-way set associative, 8 entries\n");
		break;
	case 0x6:
		printf("1st-level instruction cache: 8 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x8:
		printf("1st-level instruction cache: 16 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x9:
		printf("1st-level instruction cache: 32 KB, 4-way set associative, 64 byte line size\n");
		break;
	case 0xa:
		printf("1st-level data cache: 8 KB, 2-way set associative, 32 byte line size\n");
		break;
	case 0xb:
		printf("Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries\n");
		break;
	case 0xc:
		printf("1st-level data cache: 16 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0xd:
		printf("1st-level data cache: 16 KBytes, 4-way set associative, 64 byte line size");
		break;
	case 0xe:
		printf("1st-level data cache: 24 KBytes, 6-way set associative, 64 byte line size\n");
		break;
	case 0x1d:
		printf("2nd-level cache: 128 KBytes, 2-way set associative, 64 byte line size\n");
		break;
	case 0x21:
		printf("2nd-level cache: 256 KBytes, 8-way set associative, 64 byte line size\n");
		break;
	case 0x22:
		printf("3rd-level cache: 512 KB, 4-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x23:
		printf("3rd-level cache: 1 MB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x24:
		printf("2nd-level cache: 1 MBytes, 16-way set associative, 64 byte line size\n");
		break;
	case 0x25:
		printf("3rd-level cache: 2 MB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x29:
		printf("3rd-level cache: 4 MB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x2c:
		printf("1st-level data cache: 32 KB, 8-way set associative, 64 byte line size\n");
		break;
	case 0x30:
		printf("1st-level instruction cache: 32 KB, 8-way set associative, 64 byte line size\n");
		break;
	case 0x39: /* De-listed in SDM rev. 54 */
		printf("2nd-level cache: 128 KB, 4-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x3b: /* De-listed in SDM rev. 54 */
		printf("2nd-level cache: 128 KB, 2-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x3c: /* De-listed in SDM rev. 54 */
		printf("2nd-level cache: 256 KB, 4-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x41:
		printf("2nd-level cache: 128 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x42:
		printf("2nd-level cache: 256 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x43:
		printf("2nd-level cache: 512 KB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x44:
		printf("2nd-level cache: 1 MB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x45:
		printf("2nd-level cache: 2 MB, 4-way set associative, 32 byte line size\n");
		break;
	case 0x46:
		printf("3rd-level cache: 4 MB, 4-way set associative, 64 byte line size\n");
		break;
	case 0x47:
		printf("3rd-level cache: 8 MB, 8-way set associative, 64 byte line size\n");
		break;
	case 0x48:
		printf("2nd-level cache: 3MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0x49:
		if (CPUID_TO_FAMILY(cpu_id) == 0xf &&
		    CPUID_TO_MODEL(cpu_id) == 0x6)
			printf("3rd-level cache: 4MB, 16-way set associative, 64-byte line size\n");
		else
			printf("2nd-level cache: 4 MByte, 16-way set associative, 64 byte line size");
		break;
	case 0x4a:
		printf("3rd-level cache: 6MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0x4b:
		printf("3rd-level cache: 8MByte, 16-way set associative, 64 byte line size\n");
		break;
	case 0x4c:
		printf("3rd-level cache: 12MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0x4d:
		printf("3rd-level cache: 16MByte, 16-way set associative, 64 byte line size\n");
		break;
	case 0x4e:
		printf("2nd-level cache: 6MByte, 24-way set associative, 64 byte line size\n");
		break;
	case 0x4f:
		printf("Instruction TLB: 4 KByte pages, 32 entries\n");
		break;
	case 0x50:
		printf("Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 64 entries\n");
		break;
	case 0x51:
		printf("Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 128 entries\n");
		break;
	case 0x52:
		printf("Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 256 entries\n");
		break;
	case 0x55:
		printf("Instruction TLB: 2-MByte or 4-MByte pages, fully associative, 7 entries\n");
		break;
	case 0x56:
		printf("Data TLB0: 4 MByte pages, 4-way set associative, 16 entries\n");
		break;
	case 0x57:
		printf("Data TLB0: 4 KByte pages, 4-way associative, 16 entries\n");
		break;
	case 0x59:
		printf("Data TLB0: 4 KByte pages, fully associative, 16 entries\n");
		break;
	case 0x5a:
		printf("Data TLB0: 2-MByte or 4 MByte pages, 4-way set associative, 32 entries\n");
		break;
	case 0x5b:
		printf("Data TLB: 4 KB or 4 MB pages, fully associative, 64 entries\n");
		break;
	case 0x5c:
		printf("Data TLB: 4 KB or 4 MB pages, fully associative, 128 entries\n");
		break;
	case 0x5d:
		printf("Data TLB: 4 KB or 4 MB pages, fully associative, 256 entries\n");
		break;
	case 0x60:
		printf("1st-level data cache: 16 KB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x61:
		printf("Instruction TLB: 4 KByte pages, fully associative, 48 entries\n");
		break;
	case 0x63:
		printf("Data TLB: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries and a separate array with 1 GByte pages, 4-way set associative, 4 entries\n");
		break;
	case 0x64:
		printf("Data TLB: 4 KBytes pages, 4-way set associative, 512 entries\n");
		break;
	case 0x66:
		printf("1st-level data cache: 8 KB, 4-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x67:
		printf("1st-level data cache: 16 KB, 4-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x68:
		printf("1st-level data cache: 32 KB, 4 way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x6a:
		printf("uTLB: 4KByte pages, 8-way set associative, 64 entries\n");
		break;
	case 0x6b:
		printf("DTLB: 4KByte pages, 8-way set associative, 256 entries\n");
		break;
	case 0x6c:
		printf("DTLB: 2M/4M pages, 8-way set associative, 128 entries\n");
		break;
	case 0x6d:
		printf("DTLB: 1 GByte pages, fully associative, 16 entries\n");
		break;
	case 0x70:
		printf("Trace cache: 12K-uops, 8-way set associative\n");
		break;
	case 0x71:
		printf("Trace cache: 16K-uops, 8-way set associative\n");
		break;
	case 0x72:
		printf("Trace cache: 32K-uops, 8-way set associative\n");
		break;
	case 0x76:
		printf("Instruction TLB: 2M/4M pages, fully associative, 8 entries\n");
		break;
	case 0x78:
		printf("2nd-level cache: 1 MB, 4-way set associative, 64-byte line size\n");
		break;
	case 0x79:
		printf("2nd-level cache: 128 KB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x7a:
		printf("2nd-level cache: 256 KB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x7b:
		printf("2nd-level cache: 512 KB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x7c:
		printf("2nd-level cache: 1 MB, 8-way set associative, sectored cache, 64 byte line size\n");
		break;
	case 0x7d:
		printf("2nd-level cache: 2-MB, 8-way set associative, 64-byte line size\n");
		break;
	case 0x7f:
		printf("2nd-level cache: 512-KB, 2-way set associative, 64-byte line size\n");
		break;
	case 0x80:
		printf("2nd-level cache: 512 KByte, 8-way set associative, 64-byte line size\n");
		break;
	case 0x82:
		printf("2nd-level cache: 256 KB, 8-way set associative, 32 byte line size\n");
		break;
	case 0x83:
		printf("2nd-level cache: 512 KB, 8-way set associative, 32 byte line size\n");
		break;
	case 0x84:
		printf("2nd-level cache: 1 MB, 8-way set associative, 32 byte line size\n");
		break;
	case 0x85:
		printf("2nd-level cache: 2 MB, 8-way set associative, 32 byte line size\n");
		break;
	case 0x86:
		printf("2nd-level cache: 512 KB, 4-way set associative, 64 byte line size\n");
		break;
	case 0x87:
		printf("2nd-level cache: 1 MB, 8-way set associative, 64 byte line size\n");
		break;
	case 0xa0:
		printf("DTLB: 4k pages, fully associative, 32 entries\n");
		break;
	case 0xb0:
		printf("Instruction TLB: 4 KB Pages, 4-way set associative, 128 entries\n");
		break;
	case 0xb1:
		printf("Instruction TLB: 2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries\n");
		break;
	case 0xb2:
		printf("Instruction TLB: 4KByte pages, 4-way set associative, 64 entries\n");
		break;
	case 0xb3:
		printf("Data TLB: 4 KB Pages, 4-way set associative, 128 entries\n");
		break;
	case 0xb4:
		printf("Data TLB1: 4 KByte pages, 4-way associative, 256 entries\n");
		break;
	case 0xb5:
		printf("Instruction TLB: 4KByte pages, 8-way set associative, 64 entries\n");
		break;
	case 0xb6:
		printf("Instruction TLB: 4KByte pages, 8-way set associative, 128 entries\n");
		break;
	case 0xba:
		printf("Data TLB1: 4 KByte pages, 4-way associative, 64 entries\n");
		break;
	case 0xc0:
		printf("Data TLB: 4 KByte and 4 MByte pages, 4-way associative, 8 entries\n");
		break;
	case 0xc1:
		printf("Shared 2nd-Level TLB: 4 KByte/2MByte pages, 8-way associative, 1024 entries\n");
		break;
	case 0xc2:
		printf("DTLB: 4 KByte/2 MByte pages, 4-way associative, 16 entries\n");
		break;
	case 0xc3:
		printf("Shared 2nd-Level TLB: 4 KByte /2 MByte pages, 6-way associative, 1536 entries. Also 1GBbyte pages, 4-way, 16 entries\n");
		break;
	case 0xc4:
		printf("DTLB: 2M/4M Byte pages, 4-way associative, 32 entries\n");
		break;
	case 0xca:
		printf("Shared 2nd-Level TLB: 4 KByte pages, 4-way associative, 512 entries\n");
		break;
	case 0xd0:
		printf("3rd-level cache: 512 KByte, 4-way set associative, 64 byte line size\n");
		break;
	case 0xd1:
		printf("3rd-level cache: 1 MByte, 4-way set associative, 64 byte line size\n");
		break;
	case 0xd2:
		printf("3rd-level cache: 2 MByte, 4-way set associative, 64 byte line size\n");
		break;
	case 0xd6:
		printf("3rd-level cache: 1 MByte, 8-way set associative, 64 byte line size\n");
		break;
	case 0xd7:
		printf("3rd-level cache: 2 MByte, 8-way set associative, 64 byte line size\n");
		break;
	case 0xd8:
		printf("3rd-level cache: 4 MByte, 8-way set associative, 64 byte line size\n");
		break;
	case 0xdc:
		printf("3rd-level cache: 1.5 MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0xdd:
		printf("3rd-level cache: 3 MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0xde:
		printf("3rd-level cache: 6 MByte, 12-way set associative, 64 byte line size\n");
		break;
	case 0xe2:
		printf("3rd-level cache: 2 MByte, 16-way set associative, 64 byte line size\n");
		break;
	case 0xe3:
		printf("3rd-level cache: 4 MByte, 16-way set associative, 64 byte line size\n");
		break;
	case 0xe4:
		printf("3rd-level cache: 8 MByte, 16-way set associative, 64 byte line size\n");
		break;
	case 0xea:
		printf("3rd-level cache: 12MByte, 24-way set associative, 64 byte line size\n");
		break;
	case 0xeb:
		printf("3rd-level cache: 18MByte, 24-way set associative, 64 byte line size\n");
		break;
	case 0xec:
		printf("3rd-level cache: 24MByte, 24-way set associative, 64 byte line size\n");
		break;
	case 0xf0:
		printf("64-Byte prefetching\n");
		break;
	case 0xf1:
		printf("128-Byte prefetching\n");
		break;
	}
}