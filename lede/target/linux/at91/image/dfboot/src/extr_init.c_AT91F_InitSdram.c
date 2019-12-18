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
 int /*<<< orphan*/  AT91C_BASE_PIOC ; 
 int /*<<< orphan*/  AT91F_PIO_CfgPeriph (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AT91F_InitSdram()
{
	int *pRegister;
	
	//* Configure PIOC as peripheral (D16/D31)
	
	AT91F_PIO_CfgPeriph(
		AT91C_BASE_PIOC, // PIO controller base address
		0xFFFF0030,
		0
	);
	
	//*Init SDRAM
	pRegister = (int *)0xFFFFFF98;
	*pRegister = 0x2188c155; 
	pRegister = (int *)0xFFFFFF90;
	*pRegister = 0x2; 
	pRegister = (int *)0x20000000;
	*pRegister = 0; 
	pRegister = (int *)0xFFFFFF90;
	*pRegister = 0x4; 
	pRegister = (int *)0x20000000;
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	*pRegister = 0; 
	pRegister = (int *)0xFFFFFF90;
	*pRegister = 0x3; 
	pRegister = (int *)0x20000080;
	*pRegister = 0; 

	pRegister = (int *)0xFFFFFF94;
	*pRegister = 0x2e0; 
	pRegister = (int *)0x20000000;
	*pRegister = 0; 

	pRegister = (int *)0xFFFFFF90;
	*pRegister = 0x00; 
	pRegister = (int *)0x20000000;
	*pRegister = 0; 
}