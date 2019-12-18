#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* CRC32 ) (unsigned char const*,unsigned int,unsigned int*) ;} ;

/* Variables and functions */
 unsigned int AT91C_BOOT_ADDR ; 
 int /*<<< orphan*/  AT91C_BOOT_DATAFLASH_ADDR ; 
 scalar_t__ AT91C_DATAFLASH_OK ; 
 scalar_t__ AT91C_OFFSET_VECT6 ; 
 int IMAGE_BAD_SIZE ; 
 int IMAGE_CRC_ERROR ; 
 int IMAGE_READ_FAILURE ; 
 int SUCCESS ; 
 int crc1 ; 
 int crc2 ; 
 TYPE_1__* pAT91 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_dataflash (int /*<<< orphan*/ ,unsigned int volatile,char*) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int AT91F_LoadBoot(void)
{
//	volatile unsigned int crc1 = 0, crc2 = 0;
	volatile unsigned int SizeToDownload = 0x21400;
	volatile unsigned int AddressToDownload = AT91C_BOOT_ADDR;

#if 0
	/* Read vector 6 to extract size to load */	
	if (read_dataflash(AT91C_BOOT_DATAFLASH_ADDR, 32,
	                   (char *)AddressToDownload) != AT91C_DATAFLASH_OK)
	{
		printf("Bad Code Size\n");
		return IMAGE_BAD_SIZE;
	}
	/* calculate the size to download */
	SizeToDownload = *(int *)(AddressToDownload + AT91C_OFFSET_VECT6);
#endif
	
//	printf("\nLoad UBOOT from dataflash[%x] to SDRAM[%x]\n",
//	       AT91C_BOOT_DATAFLASH_ADDR, AT91C_BOOT_ADDR);
	if (read_dataflash(AT91C_BOOT_DATAFLASH_ADDR, SizeToDownload + 8,
	                   (char *)AddressToDownload) != AT91C_DATAFLASH_OK)
	{
		printf("F DF RD\n");
		return IMAGE_READ_FAILURE;
	}
#if 0
	pAT91->CRC32((const unsigned char *)AT91C_BOOT_ADDR,
	             (unsigned int)SizeToDownload , (unsigned int *)&crc2);
	crc1 = (int)(*(char *)(AddressToDownload + SizeToDownload)) +
	       (int)(*(char *)(AddressToDownload + SizeToDownload + 1) << 8) +
	       (int)(*(char *)(AddressToDownload + SizeToDownload + 2) << 16) +
	       (int)(*(char *)(AddressToDownload + SizeToDownload + 3) << 24);

	/* Restore the value of Vector 6 */
	*(int *)(AddressToDownload + AT91C_OFFSET_VECT6) =
		*(int *)(AddressToDownload + SizeToDownload + 4);
	
	if (crc1 != crc2) {
		printf("DF CRC bad %x != %x\n",crc1,crc2);
	 	return	IMAGE_CRC_ERROR;
	}
#endif
	return SUCCESS;
}