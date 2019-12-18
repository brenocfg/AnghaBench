#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {int /*<<< orphan*/  Filename; } ;
struct TYPE_4__ {int /*<<< orphan*/  NameColumn; int /*<<< orphan*/  ByteOffset; int /*<<< orphan*/  Line; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
#define  ASL_WARNING2 129 
#define  ASL_WARNING3 128 
 int /*<<< orphan*/  AslCommonError (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* AslGbl_Files ; 
 int AslGbl_WarningLevel ; 

void
DtNameError (
    UINT8                   Level,
    UINT16                  MessageId,
    DT_FIELD                *FieldObject,
    char                    *ExtraMessage)
{

    switch (Level)
    {
    case ASL_WARNING2:
    case ASL_WARNING3:

        if (AslGbl_WarningLevel < Level)
        {
            return;
        }
        break;

    default:

        break;
    }

    if (FieldObject)
    {
        AslCommonError (Level, MessageId,
            FieldObject->Line,
            FieldObject->Line,
            FieldObject->ByteOffset,
            FieldObject->NameColumn,
            AslGbl_Files[ASL_FILE_INPUT].Filename, ExtraMessage);
    }
    else
    {
        AslCommonError (Level, MessageId, 0,
            0, 0, 0, 0, ExtraMessage);
    }
}