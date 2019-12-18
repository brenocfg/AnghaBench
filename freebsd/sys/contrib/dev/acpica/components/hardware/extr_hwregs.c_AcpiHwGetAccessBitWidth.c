#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT64 ;
struct TYPE_3__ {int BitOffset; int BitWidth; scalar_t__ SpaceId; scalar_t__ AccessWidth; } ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 int ACPI_ACCESS_BIT_WIDTH (scalar_t__) ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 scalar_t__ ACPI_IS_ALIGNED (int,int) ; 
 scalar_t__ ACPI_IS_POWER_OF_TWO (int) ; 
 int ACPI_ROUND_UP_POWER_OF_TWO_8 (int) ; 

__attribute__((used)) static UINT8
AcpiHwGetAccessBitWidth (
    UINT64                  Address,
    ACPI_GENERIC_ADDRESS    *Reg,
    UINT8                   MaxBitWidth)
{
    UINT8                   AccessBitWidth;


    /*
     * GAS format "register", used by FADT:
     *  1. Detected if BitOffset is 0 and BitWidth is 8/16/32/64;
     *  2. AccessSize field is ignored and BitWidth field is used for
     *     determining the boundary of the IO accesses.
     * GAS format "region", used by APEI registers:
     *  1. Detected if BitOffset is not 0 or BitWidth is not 8/16/32/64;
     *  2. AccessSize field is used for determining the boundary of the
     *     IO accesses;
     *  3. BitOffset/BitWidth fields are used to describe the "region".
     *
     * Note: This algorithm assumes that the "Address" fields should always
     *       contain aligned values.
     */
    if (!Reg->BitOffset && Reg->BitWidth &&
        ACPI_IS_POWER_OF_TWO (Reg->BitWidth) &&
        ACPI_IS_ALIGNED (Reg->BitWidth, 8))
    {
        AccessBitWidth = Reg->BitWidth;
    }
    else if (Reg->AccessWidth)
    {
        AccessBitWidth = ACPI_ACCESS_BIT_WIDTH (Reg->AccessWidth);
    }
    else
    {
        AccessBitWidth = ACPI_ROUND_UP_POWER_OF_TWO_8 (
            Reg->BitOffset + Reg->BitWidth);
        if (AccessBitWidth <= 8)
        {
            AccessBitWidth = 8;
        }
        else
        {
            while (!ACPI_IS_ALIGNED (Address, AccessBitWidth >> 3))
            {
                AccessBitWidth >>= 1;
            }
        }
    }

    /* Maximum IO port access bit width is 32 */

    if (Reg->SpaceId == ACPI_ADR_SPACE_SYSTEM_IO)
    {
        MaxBitWidth = 32;
    }

    /*
     * Return access width according to the requested maximum access bit width,
     * as the caller should know the format of the register and may enforce
     * a 32-bit accesses.
     */
    if (AccessBitWidth < MaxBitWidth)
    {
        return (AccessBitWidth);
    }
    return (MaxBitWidth);
}