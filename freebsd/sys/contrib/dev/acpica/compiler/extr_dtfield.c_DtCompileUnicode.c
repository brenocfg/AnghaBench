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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_3__ {char* Value; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 size_t strlen (char*) ; 

__attribute__((used)) static void
DtCompileUnicode (
    UINT8                   *Buffer,
    DT_FIELD                *Field,
    UINT32                  ByteLength)
{
    UINT32                  Count;
    UINT32                  i;
    char                    *AsciiString;
    UINT16                  *UnicodeString;


    AsciiString = Field->Value;
    UnicodeString = (UINT16 *) Buffer;
    Count = strlen (AsciiString) + 1;

    /* Convert to Unicode string (including null terminator) */

    for (i = 0; i < Count; i++)
    {
        UnicodeString[i] = (UINT16) AsciiString[i];
    }
}