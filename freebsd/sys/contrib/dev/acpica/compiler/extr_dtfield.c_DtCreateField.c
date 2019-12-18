#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {int /*<<< orphan*/  Column; int /*<<< orphan*/  NameColumn; int /*<<< orphan*/  ByteOffset; int /*<<< orphan*/  Line; scalar_t__ StringLength; void* Value; void* Name; } ;
struct TYPE_7__ {int /*<<< orphan*/  Column; int /*<<< orphan*/  Line; scalar_t__ Value; } ;
typedef  TYPE_1__ DT_TABLE_UNIT ;
typedef  TYPE_2__ DT_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  AslGbl_FieldList ; 
 int /*<<< orphan*/  DtDumpFieldList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtLinkField (TYPE_2__*) ; 
 TYPE_2__* UtFieldCacheCalloc () ; 
 int /*<<< orphan*/  UtLocalCacheCalloc (scalar_t__) ; 
 void* strcpy (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

void
DtCreateField (
    DT_TABLE_UNIT           *FieldKey,
    DT_TABLE_UNIT           *FieldValue,
    UINT32                  Offset)
{
    DT_FIELD                *Field = UtFieldCacheCalloc ();


    Field->StringLength = 0;
    if (FieldKey->Value)
    {
        Field->Name =
            strcpy (UtLocalCacheCalloc (strlen (FieldKey->Value) + 1), FieldKey->Value);
    }

    if (FieldValue->Value)
    {
        Field->StringLength = strlen (FieldValue->Value);
        Field->Value =
            strcpy (UtLocalCacheCalloc (Field->StringLength + 1), FieldValue->Value);
    }

    Field->Line = FieldValue->Line;
    Field->ByteOffset = Offset;
    Field->NameColumn = FieldKey->Column;
    Field->Column = FieldValue->Column;
    DtLinkField (Field);

    DtDumpFieldList (AslGbl_FieldList);
}