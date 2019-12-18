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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (scalar_t__) ; 

__attribute__((used)) static UINT32
AcpiRsStreamOptionLength (
    UINT32                  ResourceLength,
    UINT32                  MinimumAmlResourceLength)
{
    UINT32                  StringLength = 0;


    ACPI_FUNCTION_ENTRY ();


    /*
     * The ResourceSourceIndex and ResourceSource are optional elements of
     * some Large-type resource descriptors.
     */

    /*
     * If the length of the actual resource descriptor is greater than the
     * ACPI spec-defined minimum length, it means that a ResourceSourceIndex
     * exists and is followed by a (required) null terminated string. The
     * string length (including the null terminator) is the resource length
     * minus the minimum length, minus one byte for the ResourceSourceIndex
     * itself.
     */
    if (ResourceLength > MinimumAmlResourceLength)
    {
        /* Compute the length of the optional string */

        StringLength = ResourceLength - MinimumAmlResourceLength - 1;
    }

    /*
     * Round the length up to a multiple of the native word in order to
     * guarantee that the entire resource descriptor is native word aligned
     */
    return ((UINT32) ACPI_ROUND_UP_TO_NATIVE_WORD (StringLength));
}