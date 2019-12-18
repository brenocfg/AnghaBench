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
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_3__ {int SpaceId; int BitWidth; scalar_t__ AccessWidth; scalar_t__ BitOffset; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ ACPI_GENERIC_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int ACPI_FADT_GPE_REGISTER ; 
 int /*<<< orphan*/  ACPI_MOVE_64_TO_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_INFO ; 

__attribute__((used)) static void
AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *GenericAddress,
    UINT8                   SpaceId,
    UINT8                   ByteWidth,
    UINT64                  Address,
    const char              *RegisterName,
    UINT8                   Flags)
{
    UINT8                   BitWidth;


    /*
     * Bit width field in the GAS is only one byte long, 255 max.
     * Check for BitWidth overflow in GAS.
     */
    BitWidth = (UINT8) (ByteWidth * 8);
    if (ByteWidth > 31)     /* (31*8)=248, (32*8)=256 */
    {
        /*
         * No error for GPE blocks, because we do not use the BitWidth
         * for GPEs, the legacy length (ByteWidth) is used instead to
         * allow for a large number of GPEs.
         */
        if (!(Flags & ACPI_FADT_GPE_REGISTER))
        {
            ACPI_ERROR ((AE_INFO,
                "%s - 32-bit FADT register is too long (%u bytes, %u bits) "
                "to convert to GAS struct - 255 bits max, truncating",
                RegisterName, ByteWidth, (ByteWidth * 8)));
        }

        BitWidth = 255;
    }

    /*
     * The 64-bit Address field is non-aligned in the byte packed
     * GAS struct.
     */
    ACPI_MOVE_64_TO_64 (&GenericAddress->Address, &Address);

    /* All other fields are byte-wide */

    GenericAddress->SpaceId = SpaceId;
    GenericAddress->BitWidth = BitWidth;
    GenericAddress->BitOffset = 0;
    GenericAddress->AccessWidth = 0; /* Access width ANY */
}