#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {size_t Type; } ;
struct TYPE_7__ {size_t ConnectionType; } ;
struct TYPE_6__ {int /*<<< orphan*/  ResourceType; } ;
struct TYPE_9__ {int DescriptorType; TYPE_3__ CommonSerialBus; TYPE_2__ Gpio; TYPE_1__ Address; } ;
typedef  TYPE_4__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_RESOURCE_TAG ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADDRESS_TYPE_IO_RANGE ; 
 int /*<<< orphan*/  ACPI_ADDRESS_TYPE_MEMORY_RANGE ; 
#define  ACPI_RESOURCE_NAME_ADDRESS16 133 
#define  ACPI_RESOURCE_NAME_ADDRESS32 132 
#define  ACPI_RESOURCE_NAME_ADDRESS64 131 
#define  ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64 130 
#define  ACPI_RESOURCE_NAME_GPIO 129 
#define  ACPI_RESOURCE_NAME_SERIAL_BUS 128 
 size_t AML_RESOURCE_MAX_GPIOTYPE ; 
 size_t AML_RESOURCE_MAX_SERIALBUSTYPE ; 
 int /*<<< orphan*/  const* AcpiDmIoFlagTags ; 
 int /*<<< orphan*/  const* AcpiDmMemoryFlagTags ; 
 char* AcpiDmSearchTagList (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** AcpiGbl_GpioResourceTags ; 
 int /*<<< orphan*/ ** AcpiGbl_ResourceTags ; 
 int /*<<< orphan*/ ** AcpiGbl_SerialResourceTags ; 

__attribute__((used)) static char *
AcpiDmGetResourceTag (
    UINT32                  BitIndex,
    AML_RESOURCE            *Resource,
    UINT8                   ResourceIndex)
{
    const ACPI_RESOURCE_TAG *TagList;
    char                    *Tag = NULL;


    /* Get the tag list for this resource descriptor type */

    TagList = AcpiGbl_ResourceTags[ResourceIndex];

    /*
     * Handle descriptors that have multiple subtypes
     */
    switch (Resource->DescriptorType)
    {
    case ACPI_RESOURCE_NAME_ADDRESS16:
    case ACPI_RESOURCE_NAME_ADDRESS32:
    case ACPI_RESOURCE_NAME_ADDRESS64:
    case ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64:
        /*
         * Subtype differentiation is the flags.
         * Kindof brute force, but just blindly search for an index match
         */
        if (Resource->Address.ResourceType == ACPI_ADDRESS_TYPE_MEMORY_RANGE)
        {
            Tag = AcpiDmSearchTagList (BitIndex, AcpiDmMemoryFlagTags);
        }
        else if (Resource->Address.ResourceType == ACPI_ADDRESS_TYPE_IO_RANGE)
        {
            Tag = AcpiDmSearchTagList (BitIndex, AcpiDmIoFlagTags);
        }

        /* If we found a match, all done. Else, drop to normal search below */

        if (Tag)
        {
            return (Tag);
        }
        break;

    case ACPI_RESOURCE_NAME_GPIO:

        /* GPIO connection has 2 subtypes: Interrupt and I/O */

        if (Resource->Gpio.ConnectionType > AML_RESOURCE_MAX_GPIOTYPE)
        {
            return (NULL);
        }

        TagList = AcpiGbl_GpioResourceTags[Resource->Gpio.ConnectionType];
        break;

    case ACPI_RESOURCE_NAME_SERIAL_BUS:

        /* SerialBus has 3 subtypes: I2C, SPI, and UART */

        if ((Resource->CommonSerialBus.Type == 0) ||
            (Resource->CommonSerialBus.Type > AML_RESOURCE_MAX_SERIALBUSTYPE))
        {
            return (NULL);
        }

        TagList = AcpiGbl_SerialResourceTags[Resource->CommonSerialBus.Type];
        break;

    default:

        break;
    }

    /* Search for a match against the BitIndex */

    if (TagList)
    {
        Tag = AcpiDmSearchTagList (BitIndex, TagList);
    }

    return (Tag);
}