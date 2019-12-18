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
typedef  size_t UINT32 ;
struct TYPE_3__ {char* ExternalName; int NumSegments; char const* NextExternalChar; scalar_t__ NumCarats; scalar_t__ Length; int /*<<< orphan*/  FullyQualified; } ;
typedef  TYPE_1__ ACPI_NAMESTRING_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_IS_PARENT_PREFIX (char const) ; 
 scalar_t__ ACPI_IS_PATH_SEPARATOR (char const) ; 
 scalar_t__ ACPI_IS_ROOT_PREFIX (char const) ; 
 int ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

void
AcpiNsGetInternalNameLength (
    ACPI_NAMESTRING_INFO    *Info)
{
    const char              *NextExternalChar;
    UINT32                  i;


    ACPI_FUNCTION_ENTRY ();


    NextExternalChar = Info->ExternalName;
    Info->NumCarats = 0;
    Info->NumSegments = 0;
    Info->FullyQualified = FALSE;

    /*
     * For the internal name, the required length is 4 bytes per segment,
     * plus 1 each for RootPrefix, MultiNamePrefixOp, segment count,
     * trailing null (which is not really needed, but no there's harm in
     * putting it there)
     *
     * strlen() + 1 covers the first NameSeg, which has no path separator
     */
    if (ACPI_IS_ROOT_PREFIX (*NextExternalChar))
    {
        Info->FullyQualified = TRUE;
        NextExternalChar++;

        /* Skip redundant RootPrefix, like \\_SB.PCI0.SBRG.EC0 */

        while (ACPI_IS_ROOT_PREFIX (*NextExternalChar))
        {
            NextExternalChar++;
        }
    }
    else
    {
        /* Handle Carat prefixes */

        while (ACPI_IS_PARENT_PREFIX (*NextExternalChar))
        {
            Info->NumCarats++;
            NextExternalChar++;
        }
    }

    /*
     * Determine the number of ACPI name "segments" by counting the number of
     * path separators within the string. Start with one segment since the
     * segment count is [(# separators) + 1], and zero separators is ok.
     */
    if (*NextExternalChar)
    {
        Info->NumSegments = 1;
        for (i = 0; NextExternalChar[i]; i++)
        {
            if (ACPI_IS_PATH_SEPARATOR (NextExternalChar[i]))
            {
                Info->NumSegments++;
            }
        }
    }

    Info->Length = (ACPI_NAMESEG_SIZE * Info->NumSegments) +
        4 + Info->NumCarats;

    Info->NextExternalChar = NextExternalChar;
}