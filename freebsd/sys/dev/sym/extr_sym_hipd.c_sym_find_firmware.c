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
struct sym_pci_chip {int features; } ;
struct sym_fw {int dummy; } ;

/* Variables and functions */
 int FE_DAC ; 
 int FE_LDSTR ; 
 int FE_NOPM ; 
 int FE_PFEN ; 
 struct sym_fw const sym_fw1 ; 
 struct sym_fw const sym_fw2 ; 

__attribute__((used)) static const struct sym_fw *
sym_find_firmware(const struct sym_pci_chip *chip)
{
	if (chip->features & FE_LDSTR)
		return &sym_fw2;
#ifdef	SYM_CONF_GENERIC_SUPPORT
	else if (!(chip->features & (FE_PFEN|FE_NOPM|FE_DAC)))
		return &sym_fw1;
#endif
	else
		return NULL;
}