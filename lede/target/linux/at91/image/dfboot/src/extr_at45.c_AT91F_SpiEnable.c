#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* PIO_CODR; void* PIO_OER; void* PIO_PER; } ;
struct TYPE_3__ {int SPI_MR; int /*<<< orphan*/  SPI_CR; } ;

/* Variables and functions */
 TYPE_2__* AT91C_BASE_PIOB ; 
 TYPE_1__* AT91C_BASE_SPI ; 
 void* AT91C_PIO_PB7 ; 
 int AT91C_SPI_PCS ; 
 int AT91C_SPI_PCS0_SERIAL_DATAFLASH ; 
 int AT91C_SPI_PCS3_DATAFLASH_CARD ; 
 int /*<<< orphan*/  AT91C_SPI_SPIEN ; 

__attribute__((used)) static void AT91F_SpiEnable(int cs) {
	switch(cs) {
	case 0:	/* Configure SPI CS0 for Serial DataFlash AT45DBxx */
		AT91C_BASE_SPI->SPI_MR &= 0xFFF0FFFF;
		AT91C_BASE_SPI->SPI_MR |= ((AT91C_SPI_PCS0_SERIAL_DATAFLASH << 16) & AT91C_SPI_PCS);
		break;
	case 3:	/* Configure SPI CS3 for Serial DataFlash Card */
		/* Set up PIO SDC_TYPE to switch on DataFlash Card and not MMC/SDCard */
		AT91C_BASE_PIOB->PIO_PER = AT91C_PIO_PB7;	/* Set in PIO mode */
		AT91C_BASE_PIOB->PIO_OER = AT91C_PIO_PB7;	/* Configure in output */
		/* Clear Output */
		AT91C_BASE_PIOB->PIO_CODR = AT91C_PIO_PB7;
		/* Configure PCS */
		AT91C_BASE_SPI->SPI_MR &= 0xFFF0FFFF;
		AT91C_BASE_SPI->SPI_MR |= ((AT91C_SPI_PCS3_DATAFLASH_CARD<<16) & AT91C_SPI_PCS);
		break;
	}

	/* SPI_Enable */
	AT91C_BASE_SPI->SPI_CR = AT91C_SPI_SPIEN;
}