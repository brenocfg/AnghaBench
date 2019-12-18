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
typedef  int UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/ * AcpiGbl_PtypDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int,...) ; 

__attribute__((used)) static void
AcpiDmPinConfig(
    UINT8                   PinConfigType,
    UINT32                  PinConfigValue)
{
    if (PinConfigType <= 13)
    {
        AcpiOsPrintf ("0x%2.2X /* %s */, ", PinConfigType,
            AcpiGbl_PtypDecode[PinConfigType]);
    }
    else
    {
        AcpiOsPrintf ("0x%2.2X, /* Vendor Defined */ ", PinConfigType);
    }

    /* PinConfigValue */

    AcpiOsPrintf ("0x%4.4X,\n", PinConfigValue);
}