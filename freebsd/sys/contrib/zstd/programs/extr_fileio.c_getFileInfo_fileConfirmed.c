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
struct TYPE_4__ {int nbFiles; int /*<<< orphan*/  compressedSize; } ;
typedef  TYPE_1__ fileInfo_t ;
typedef  int /*<<< orphan*/  InfoError ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  FIO_analyzeFrames (TYPE_1__*,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * FIO_openSrcFile (char const*) ; 
 int /*<<< orphan*/  UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  info_file_error ; 

__attribute__((used)) static InfoError
getFileInfo_fileConfirmed(fileInfo_t* info, const char* inFileName)
{
    InfoError status;
    FILE* const srcFile = FIO_openSrcFile(inFileName);
    ERROR_IF(srcFile == NULL, info_file_error, "Error: could not open source file %s", inFileName);

    info->compressedSize = UTIL_getFileSize(inFileName);
    status = FIO_analyzeFrames(info, srcFile);

    fclose(srcFile);
    info->nbFiles = 1;
    return status;
}