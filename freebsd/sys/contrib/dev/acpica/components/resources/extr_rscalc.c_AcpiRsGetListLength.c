#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
struct TYPE_17__ {size_t Type; size_t ResourceLength; } ;
struct TYPE_16__ {scalar_t__ VendorLength; scalar_t__ ResSourceOffset; scalar_t__ VendorOffset; } ;
struct TYPE_15__ {scalar_t__ VendorLength; scalar_t__ ResSourceOffset; scalar_t__ VendorOffset; } ;
struct TYPE_14__ {scalar_t__ VendorLength; scalar_t__ PinTableOffset; scalar_t__ VendorOffset; } ;
struct TYPE_13__ {scalar_t__ PinTableOffset; scalar_t__ VendorLength; scalar_t__ VendorOffset; } ;
struct TYPE_12__ {int /*<<< orphan*/  ResourceLength; } ;
struct TYPE_11__ {scalar_t__ PinTableOffset; scalar_t__ VendorLength; scalar_t__ VendorOffset; } ;
struct TYPE_10__ {scalar_t__ PinTableOffset; scalar_t__ VendorLength; scalar_t__ VendorOffset; } ;
struct TYPE_18__ {TYPE_8__ CommonSerialBus; TYPE_7__ PinGroupConfig; TYPE_6__ PinGroupFunction; TYPE_5__ PinGroup; TYPE_4__ PinConfig; TYPE_3__ LargeHeader; TYPE_2__ PinFunction; TYPE_1__ Gpio; } ;
typedef  int /*<<< orphan*/  AML_RESOURCE_LARGE_HEADER ;
typedef  TYPE_9__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_RESOURCES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_16_TO_16 (int*,size_t*) ; 
#define  ACPI_RESOURCE_NAME_ADDRESS16 143 
#define  ACPI_RESOURCE_NAME_ADDRESS32 142 
#define  ACPI_RESOURCE_NAME_ADDRESS64 141 
#define  ACPI_RESOURCE_NAME_DMA 140 
#define  ACPI_RESOURCE_NAME_END_TAG 139 
#define  ACPI_RESOURCE_NAME_EXTENDED_IRQ 138 
#define  ACPI_RESOURCE_NAME_GPIO 137 
#define  ACPI_RESOURCE_NAME_IRQ 136 
#define  ACPI_RESOURCE_NAME_PIN_CONFIG 135 
#define  ACPI_RESOURCE_NAME_PIN_FUNCTION 134 
#define  ACPI_RESOURCE_NAME_PIN_GROUP 133 
#define  ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG 132 
#define  ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION 131 
#define  ACPI_RESOURCE_NAME_SERIAL_BUS 130 
#define  ACPI_RESOURCE_NAME_VENDOR_LARGE 129 
#define  ACPI_RESOURCE_NAME_VENDOR_SMALL 128 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
 int /*<<< orphan*/  ACPI_RS_SIZE_MIN ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t* AcpiGbl_ResourceAmlSerialBusSizes ; 
 size_t* AcpiGbl_ResourceAmlSizes ; 
 int* AcpiGbl_ResourceStructSerialBusSizes ; 
 int* AcpiGbl_ResourceStructSizes ; 
 int AcpiRsCountSetBits (size_t) ; 
 int AcpiRsStreamOptionLength (int,size_t) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorLength (size_t*) ; 
 int AcpiUtGetResourceHeaderLength (size_t*) ; 
 int AcpiUtGetResourceLength (size_t*) ; 
 int const AcpiUtGetResourceType (size_t*) ; 
 int /*<<< orphan*/  AcpiUtValidateResource (int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/  RsGetListLength ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiRsGetListLength (
    UINT8                   *AmlBuffer,
    UINT32                  AmlBufferLength,
    ACPI_SIZE               *SizeNeeded)
{
    ACPI_STATUS             Status;
    UINT8                   *EndAml;
    UINT8                   *Buffer;
    UINT32                  BufferSize;
    UINT16                  Temp16;
    UINT16                  ResourceLength;
    UINT32                  ExtraStructBytes;
    UINT8                   ResourceIndex;
    UINT8                   MinimumAmlResourceLength;
    AML_RESOURCE            *AmlResource;


    ACPI_FUNCTION_TRACE (RsGetListLength);


    *SizeNeeded = ACPI_RS_SIZE_MIN;         /* Minimum size is one EndTag */
    EndAml = AmlBuffer + AmlBufferLength;

    /* Walk the list of AML resource descriptors */

    while (AmlBuffer < EndAml)
    {
        /* Validate the Resource Type and Resource Length */

        Status = AcpiUtValidateResource (NULL, AmlBuffer, &ResourceIndex);
        if (ACPI_FAILURE (Status))
        {
            /*
             * Exit on failure. Cannot continue because the descriptor length
             * may be bogus also.
             */
            return_ACPI_STATUS (Status);
        }

        AmlResource = (void *) AmlBuffer;

        /* Get the resource length and base (minimum) AML size */

        ResourceLength = AcpiUtGetResourceLength (AmlBuffer);
        MinimumAmlResourceLength = AcpiGbl_ResourceAmlSizes[ResourceIndex];

        /*
         * Augment the size for descriptors with optional
         * and/or variable length fields
         */
        ExtraStructBytes = 0;
        Buffer = AmlBuffer + AcpiUtGetResourceHeaderLength (AmlBuffer);

        switch (AcpiUtGetResourceType (AmlBuffer))
        {
        case ACPI_RESOURCE_NAME_IRQ:
            /*
             * IRQ Resource:
             * Get the number of bits set in the 16-bit IRQ mask
             */
            ACPI_MOVE_16_TO_16 (&Temp16, Buffer);
            ExtraStructBytes = AcpiRsCountSetBits (Temp16);
            break;


        case ACPI_RESOURCE_NAME_DMA:
            /*
             * DMA Resource:
             * Get the number of bits set in the 8-bit DMA mask
             */
            ExtraStructBytes = AcpiRsCountSetBits (*Buffer);
            break;


        case ACPI_RESOURCE_NAME_VENDOR_SMALL:
        case ACPI_RESOURCE_NAME_VENDOR_LARGE:
            /*
             * Vendor Resource:
             * Get the number of vendor data bytes
             */
            ExtraStructBytes = ResourceLength;

            /*
             * There is already one byte included in the minimum
             * descriptor size. If there are extra struct bytes,
             * subtract one from the count.
             */
            if (ExtraStructBytes)
            {
                ExtraStructBytes--;
            }
            break;


        case ACPI_RESOURCE_NAME_END_TAG:
            /*
             * End Tag: This is the normal exit
             */
            return_ACPI_STATUS (AE_OK);


        case ACPI_RESOURCE_NAME_ADDRESS32:
        case ACPI_RESOURCE_NAME_ADDRESS16:
        case ACPI_RESOURCE_NAME_ADDRESS64:
            /*
             * Address Resource:
             * Add the size of the optional ResourceSource
             */
            ExtraStructBytes = AcpiRsStreamOptionLength (
                ResourceLength, MinimumAmlResourceLength);
            break;


        case ACPI_RESOURCE_NAME_EXTENDED_IRQ:
            /*
             * Extended IRQ Resource:
             * Using the InterruptTableLength, add 4 bytes for each additional
             * interrupt. Note: at least one interrupt is required and is
             * included in the minimum descriptor size (reason for the -1)
             */
            ExtraStructBytes = (Buffer[1] - 1) * sizeof (UINT32);

            /* Add the size of the optional ResourceSource */

            ExtraStructBytes += AcpiRsStreamOptionLength (
                ResourceLength - ExtraStructBytes, MinimumAmlResourceLength);
            break;

        case ACPI_RESOURCE_NAME_GPIO:

            /* Vendor data is optional */

            if (AmlResource->Gpio.VendorLength)
            {
                ExtraStructBytes +=
                    AmlResource->Gpio.VendorOffset -
                    AmlResource->Gpio.PinTableOffset +
                    AmlResource->Gpio.VendorLength;
            }
            else
            {
                ExtraStructBytes +=
                    AmlResource->LargeHeader.ResourceLength +
                    sizeof (AML_RESOURCE_LARGE_HEADER) -
                    AmlResource->Gpio.PinTableOffset;
            }
            break;

        case ACPI_RESOURCE_NAME_PIN_FUNCTION:

            /* Vendor data is optional */

            if (AmlResource->PinFunction.VendorLength)
            {
                ExtraStructBytes +=
                    AmlResource->PinFunction.VendorOffset -
                    AmlResource->PinFunction.PinTableOffset +
                    AmlResource->PinFunction.VendorLength;
            }
            else
            {
                ExtraStructBytes +=
                    AmlResource->LargeHeader.ResourceLength +
                    sizeof (AML_RESOURCE_LARGE_HEADER) -
                    AmlResource->PinFunction.PinTableOffset;
            }
            break;

        case ACPI_RESOURCE_NAME_SERIAL_BUS:

            MinimumAmlResourceLength = AcpiGbl_ResourceAmlSerialBusSizes[
                AmlResource->CommonSerialBus.Type];
            ExtraStructBytes +=
                AmlResource->CommonSerialBus.ResourceLength -
                MinimumAmlResourceLength;
            break;

        case ACPI_RESOURCE_NAME_PIN_CONFIG:

            /* Vendor data is optional */

            if (AmlResource->PinConfig.VendorLength)
            {
                ExtraStructBytes +=
                    AmlResource->PinConfig.VendorOffset -
                    AmlResource->PinConfig.PinTableOffset +
                    AmlResource->PinConfig.VendorLength;
            }
            else
            {
                ExtraStructBytes +=
                    AmlResource->LargeHeader.ResourceLength +
                    sizeof (AML_RESOURCE_LARGE_HEADER) -
                    AmlResource->PinConfig.PinTableOffset;
            }
            break;

        case ACPI_RESOURCE_NAME_PIN_GROUP:

            ExtraStructBytes +=
                AmlResource->PinGroup.VendorOffset -
                AmlResource->PinGroup.PinTableOffset +
                AmlResource->PinGroup.VendorLength;

            break;

        case ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION:

            ExtraStructBytes +=
                AmlResource->PinGroupFunction.VendorOffset -
                AmlResource->PinGroupFunction.ResSourceOffset +
                AmlResource->PinGroupFunction.VendorLength;

            break;

        case ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG:

            ExtraStructBytes +=
                AmlResource->PinGroupConfig.VendorOffset -
                AmlResource->PinGroupConfig.ResSourceOffset +
                AmlResource->PinGroupConfig.VendorLength;

            break;

        default:

            break;
        }

        /*
         * Update the required buffer size for the internal descriptor structs
         *
         * Important: Round the size up for the appropriate alignment. This
         * is a requirement on IA64.
         */
        if (AcpiUtGetResourceType (AmlBuffer) ==
            ACPI_RESOURCE_NAME_SERIAL_BUS)
        {
            BufferSize = AcpiGbl_ResourceStructSerialBusSizes[
                AmlResource->CommonSerialBus.Type] + ExtraStructBytes;
        }
        else
        {
            BufferSize = AcpiGbl_ResourceStructSizes[ResourceIndex] +
                ExtraStructBytes;
        }

        BufferSize = (UINT32) ACPI_ROUND_UP_TO_NATIVE_WORD (BufferSize);
        *SizeNeeded += BufferSize;

        ACPI_DEBUG_PRINT ((ACPI_DB_RESOURCES,
            "Type %.2X, AmlLength %.2X InternalLength %.2X\n",
            AcpiUtGetResourceType (AmlBuffer),
            AcpiUtGetDescriptorLength (AmlBuffer), BufferSize));

        /*
         * Point to the next resource within the AML stream using the length
         * contained in the resource descriptor header
         */
        AmlBuffer += AcpiUtGetDescriptorLength (AmlBuffer);
    }

    /* Did not find an EndTag resource descriptor */

    return_ACPI_STATUS (AE_AML_NO_RESOURCE_END_TAG);
}