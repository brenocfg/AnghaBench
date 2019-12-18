#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  Filename; } ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslCommonError2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AslGbl_CurrentLineBuffer ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_PreprocessorError ; 
 int /*<<< orphan*/  TRUE ; 

void
PrError (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  Column)
{
#if 0
    AcpiOsPrintf ("%s (%u) : %s", AslGbl_Files[ASL_FILE_INPUT].Filename,
        AslGbl_CurrentLineNumber, AslGbl_CurrentLineBuffer);
#endif


    if (Column > 120)
    {
        Column = 0;
    }

    /* TBD: Need Logical line number? */

    AslCommonError2 (Level, MessageId,
        AslGbl_CurrentLineNumber, Column,
        AslGbl_CurrentLineBuffer,
        AslGbl_Files[ASL_FILE_INPUT].Filename, "Preprocessor");

    AslGbl_PreprocessorError = TRUE;
}