#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_4__ {char* Description; } ;
struct TYPE_3__ {char* Filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  AslCommonError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* AslGbl_FileDescs ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
FlFileError (
    UINT32                  FileId,
    UINT8                   ErrorId)
{

    sprintf (AslGbl_MsgBuffer, "\"%s\" (%s) - %s", AslGbl_Files[FileId].Filename,
        AslGbl_FileDescs[FileId].Description, strerror (errno));

    AslCommonError (ASL_ERROR, ErrorId, 0, 0, 0, 0, NULL, AslGbl_MsgBuffer);
}