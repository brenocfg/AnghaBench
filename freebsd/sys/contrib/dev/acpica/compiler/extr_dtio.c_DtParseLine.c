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
typedef  void* UINT32 ;
struct TYPE_4__ {char* Name; char* Value; void* StringLength; void* Column; void* NameColumn; void* ByteOffset; void* Line; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 void* ACPI_PTR_DIFF (char*,char*) ; 
 int /*<<< orphan*/  ACPI_RAW_TABLE_DATA_HEADER ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DtLinkField (TYPE_1__*) ; 
 char* DtTrim (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__* UtFieldCacheCalloc () ; 
 char* UtLocalCalloc (void*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,void*) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
DtParseLine (
    char                    *LineBuffer,
    UINT32                  Line,
    UINT32                  Offset)
{
    char                    *Start;
    char                    *End;
    char                    *TmpName;
    char                    *TmpValue;
    char                    *Name;
    char                    *Value;
    char                    *Colon;
    UINT32                  Length;
    DT_FIELD                *Field;
    UINT32                  Column;
    UINT32                  NameColumn;
    BOOLEAN                 IsNullString = FALSE;


    if (!LineBuffer)
    {
        return (AE_OK);
    }

    /* All lines after "Raw Table Data" are ignored */

    if (strstr (LineBuffer, ACPI_RAW_TABLE_DATA_HEADER))
    {
        return (AE_NOT_FOUND);
    }

    Colon = strchr (LineBuffer, ':');
    if (!Colon)
    {
        return (AE_OK);
    }

    Start = LineBuffer;
    End = Colon;

    while (Start < Colon)
    {
        if (*Start == '[')
        {
            /* Found left bracket, go to the right bracket */

            while (Start < Colon && *Start != ']')
            {
                Start++;
            }
        }
        else if (*Start != ' ')
        {
            break;
        }

        Start++;
    }

    /*
     * There are two column values. One for the field name,
     * and one for the field value.
     */
    Column = ACPI_PTR_DIFF (Colon, LineBuffer) + 3;
    NameColumn = ACPI_PTR_DIFF (Start, LineBuffer) + 1;

    Length = ACPI_PTR_DIFF (End, Start);

    TmpName = UtLocalCalloc (Length + 1);
    strncpy (TmpName, Start, Length);
    Name = DtTrim (TmpName);
    ACPI_FREE (TmpName);

    Start = End = (Colon + 1);
    while (*End)
    {
        /* Found left quotation, go to the right quotation and break */

        if (*End == '"')
        {
            End++;

            /* Check for an explicit null string */

            if (*End == '"')
            {
                IsNullString = TRUE;
            }
            while (*End && (*End != '"'))
            {
                End++;
            }

            End++;
            break;
        }

        /*
         * Special "comment" fields at line end, ignore them.
         * Note: normal slash-slash and slash-asterisk comments are
         * stripped already by the DtGetNextLine parser.
         *
         * TBD: Perhaps DtGetNextLine should parse the following type
         * of comments also.
         */
        if (*End == '[')
        {
            End--;
            break;
        }

        End++;
    }

    Length = ACPI_PTR_DIFF (End, Start);
    TmpValue = UtLocalCalloc (Length + 1);

    strncpy (TmpValue, Start, Length);
    Value = DtTrim (TmpValue);
    ACPI_FREE (TmpValue);

    /* Create a new field object only if we have a valid value field */

    if ((Value && *Value) || IsNullString)
    {
        Field = UtFieldCacheCalloc ();
        Field->Name = Name;
        Field->Value = Value;
        Field->Line = Line;
        Field->ByteOffset = Offset;
        Field->NameColumn = NameColumn;
        Field->Column = Column;
        Field->StringLength = Length;

        DtLinkField (Field);
    }
    /* Else -- Ignore this field, it has no valid data */

    return (AE_OK);
}