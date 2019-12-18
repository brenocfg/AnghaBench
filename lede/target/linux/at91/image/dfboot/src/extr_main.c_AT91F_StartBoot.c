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
 int /*<<< orphan*/  AT91C_BOOT_ADDR ; 
 int AT91F_LoadBoot () ; 
 scalar_t__ AT91F_ResetRegisters () ; 
 int IMAGE_ERROR ; 
 int /*<<< orphan*/  Jump (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int AT91F_StartBoot(void)
{
	int	sts;
	if((sts = AT91F_LoadBoot()) != SUCCESS) return sts;
//	printf("\n");
//	printf("PLLA[180MHz], MCK[60Mhz] ==> Start UBOOT\n");
	if (AT91F_ResetRegisters())
	{
		printf("Jump");
		Jump(AT91C_BOOT_ADDR);
//		LED_blink(0);
	}
	return	IMAGE_ERROR;
}