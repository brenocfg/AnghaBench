#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {scalar_t__ TotalLength; scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ DT_SUBTABLE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  UINT8 ; 
 char* UtLocalCacheCalloc (scalar_t__) ; 
 TYPE_1__* UtSubtableCacheCalloc () ; 

ACPI_STATUS
DtCompilePadding (
    UINT32                  Length,
    DT_SUBTABLE             **RetSubtable)
{
    DT_SUBTABLE             *Subtable;
    /* UINT8                   *Buffer; */
    char                    *String;


    Subtable = UtSubtableCacheCalloc ();

    if (Length > 0)
    {
        String = UtLocalCacheCalloc (Length);
        Subtable->Buffer = ACPI_CAST_PTR (UINT8, String);
    }

    Subtable->Length = Length;
    Subtable->TotalLength = Length;
    /* Buffer = Subtable->Buffer; */

    *RetSubtable = Subtable;
    return (AE_OK);
}