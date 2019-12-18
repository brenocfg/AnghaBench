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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ ACPI_RSDESC_SIZE ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ AcpiUtGetDescriptorLength (scalar_t__*) ; 
 scalar_t__ AcpiUtGetResourceType (scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void
AcpiDmCompareAmlResources (
    UINT8                   *Aml1Buffer,
    ACPI_RSDESC_SIZE        Aml1BufferLength,
    UINT8                   *Aml2Buffer,
    ACPI_RSDESC_SIZE        Aml2BufferLength)
{
    UINT8                   *Aml1;
    UINT8                   *Aml2;
    UINT8                   *Aml1End;
    UINT8                   *Aml2End;
    ACPI_RSDESC_SIZE        Aml1Length;
    ACPI_RSDESC_SIZE        Aml2Length;
    ACPI_RSDESC_SIZE        Offset = 0;
    UINT8                   ResourceType;
    UINT32                  Count = 0;
    UINT32                  i;


    /* Compare overall buffer sizes (may be different due to size rounding) */

    if (Aml1BufferLength != Aml2BufferLength)
    {
        AcpiOsPrintf (
            "**** Buffer length mismatch in converted "
            "AML: Original %X, New %X ****\n",
            Aml1BufferLength, Aml2BufferLength);
    }

    Aml1 = Aml1Buffer;
    Aml2 = Aml2Buffer;
    Aml1End = Aml1Buffer + Aml1BufferLength;
    Aml2End = Aml2Buffer + Aml2BufferLength;

    /* Walk the descriptor lists, comparing each descriptor */

    while ((Aml1 < Aml1End) && (Aml2 < Aml2End))
    {
        /* Get the lengths of each descriptor */

        Aml1Length = AcpiUtGetDescriptorLength (Aml1);
        Aml2Length = AcpiUtGetDescriptorLength (Aml2);
        ResourceType = AcpiUtGetResourceType (Aml1);

        /* Check for descriptor length match */

        if (Aml1Length != Aml2Length)
        {
            AcpiOsPrintf (
                "**** Length mismatch in descriptor [%.2X] type %2.2X, "
                "Offset %8.8X Len1 %X, Len2 %X ****\n",
                Count, ResourceType, Offset, Aml1Length, Aml2Length);
        }

        /* Check for descriptor byte match */

        else if (memcmp (Aml1, Aml2, Aml1Length))
        {
            AcpiOsPrintf (
                "**** Data mismatch in descriptor [%.2X] type %2.2X, "
                "Offset %8.8X ****\n",
                Count, ResourceType, Offset);

            for (i = 0; i < Aml1Length; i++)
            {
                if (Aml1[i] != Aml2[i])
                {
                    AcpiOsPrintf (
                        "Mismatch at byte offset %.2X: is %2.2X, "
                        "should be %2.2X\n",
                        i, Aml2[i], Aml1[i]);
                }
            }
        }

        /* Exit on EndTag descriptor */

        if (ResourceType == ACPI_RESOURCE_NAME_END_TAG)
        {
            return;
        }

        /* Point to next descriptor in each buffer */

        Count++;
        Offset += Aml1Length;
        Aml1 += Aml1Length;
        Aml2 += Aml2Length;
    }
}