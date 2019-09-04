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
typedef  int /*<<< orphan*/  unz_file_info ;
typedef  int /*<<< orphan*/  unzFile ;
typedef  int /*<<< orphan*/  uLong ;

/* Variables and functions */
 int unzlocal_GetCurrentFileInfoInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

extern int unzGetCurrentFileInfo (	unzFile file, unz_file_info *pfile_info,
									char *szFileName, uLong fileNameBufferSize,
									void *extraField, uLong extraFieldBufferSize,
									char *szComment, uLong commentBufferSize)
{
	return unzlocal_GetCurrentFileInfoInternal(file,pfile_info,NULL,
												szFileName,fileNameBufferSize,
												extraField,extraFieldBufferSize,
												szComment,commentBufferSize);
}