#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT32 ;
struct TYPE_5__ {int BitOffset; int BitWidth; scalar_t__ SpaceId; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;
typedef  scalar_t__ ACPI_IO_ADDRESS ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_DB_IO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_DIV_8 (int) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MASK_BITS_ABOVE_64 (int) ; 
 int /*<<< orphan*/  ACPI_SET_BITS (scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int AcpiHwGetAccessBitWidth (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  AcpiHwReadPort (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  AcpiHwValidateRegister (TYPE_1__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  AcpiOsReadMemory (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (scalar_t__) ; 
 int /*<<< orphan*/  HwRead ; 

ACPI_STATUS
AcpiHwRead (
    UINT64                  *Value,
    ACPI_GENERIC_ADDRESS    *Reg)
{
    UINT64                  Address;
    UINT8                   AccessWidth;
    UINT32                  BitWidth;
    UINT8                   BitOffset;
    UINT64                  Value64;
    UINT32                  Value32;
    UINT8                   Index;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_NAME (HwRead);


    /* Validate contents of the GAS register */

    Status = AcpiHwValidateRegister (Reg, 64, &Address);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * Initialize entire 64-bit return value to zero, convert AccessWidth
     * into number of bits based
     */
    *Value = 0;
    AccessWidth = AcpiHwGetAccessBitWidth (Address, Reg, 64);
    BitWidth = Reg->BitOffset + Reg->BitWidth;
    BitOffset = Reg->BitOffset;

    /*
     * Two address spaces supported: Memory or IO. PCI_Config is
     * not supported here because the GAS structure is insufficient
     */
    Index = 0;
    while (BitWidth)
    {
        if (BitOffset >= AccessWidth)
        {
            Value64 = 0;
            BitOffset -= AccessWidth;
        }
        else
        {
            if (Reg->SpaceId == ACPI_ADR_SPACE_SYSTEM_MEMORY)
            {
                Status = AcpiOsReadMemory ((ACPI_PHYSICAL_ADDRESS)
                    Address + Index * ACPI_DIV_8 (AccessWidth),
                    &Value64, AccessWidth);
            }
            else /* ACPI_ADR_SPACE_SYSTEM_IO, validated earlier */
            {
                Status = AcpiHwReadPort ((ACPI_IO_ADDRESS)
                    Address + Index * ACPI_DIV_8 (AccessWidth),
                    &Value32, AccessWidth);
                Value64 = (UINT64) Value32;
            }
        }

        /*
         * Use offset style bit writes because "Index * AccessWidth" is
         * ensured to be less than 64-bits by AcpiHwValidateRegister().
         */
        ACPI_SET_BITS (Value, Index * AccessWidth,
            ACPI_MASK_BITS_ABOVE_64 (AccessWidth), Value64);

        BitWidth -= BitWidth > AccessWidth ? AccessWidth : BitWidth;
        Index++;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_IO,
        "Read:  %8.8X%8.8X width %2d from %8.8X%8.8X (%s)\n",
        ACPI_FORMAT_UINT64 (*Value), AccessWidth,
        ACPI_FORMAT_UINT64 (Address), AcpiUtGetRegionName (Reg->SpaceId)));

    return (Status);
}