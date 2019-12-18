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
struct TYPE_4__ {int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_TRUE ; 
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAppendWord (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlCloseFile ; 
 int /*<<< orphan*/  ficlCreateFile ; 
 int /*<<< orphan*/  ficlDeleteFile ; 
 int /*<<< orphan*/  ficlFilePosition ; 
 int /*<<< orphan*/  ficlFileSize ; 
 int /*<<< orphan*/  ficlFileStatus ; 
 int /*<<< orphan*/  ficlFlushFile ; 
 int /*<<< orphan*/  ficlIncludeFile ; 
 int /*<<< orphan*/  ficlOpenFile ; 
 int /*<<< orphan*/  ficlReadFile ; 
 int /*<<< orphan*/  ficlReadLine ; 
 int /*<<< orphan*/  ficlRenameFile ; 
 int /*<<< orphan*/  ficlRepositionFile ; 
 int /*<<< orphan*/  ficlResizeFile ; 
 int /*<<< orphan*/  ficlSetEnv (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlWriteFile ; 
 int /*<<< orphan*/  ficlWriteLine ; 

void ficlCompileFile(FICL_SYSTEM *pSys)
{
#if FICL_WANT_FILE
    FICL_DICT *dp = pSys->dp;
    assert(dp);

    dictAppendWord(dp, "create-file", ficlCreateFile,  FW_DEFAULT);
    dictAppendWord(dp, "open-file", ficlOpenFile,  FW_DEFAULT);
    dictAppendWord(dp, "close-file", ficlCloseFile,  FW_DEFAULT);
    dictAppendWord(dp, "include-file", ficlIncludeFile,  FW_DEFAULT);
    dictAppendWord(dp, "read-file", ficlReadFile,  FW_DEFAULT);
    dictAppendWord(dp, "read-line", ficlReadLine,  FW_DEFAULT);
    dictAppendWord(dp, "write-file", ficlWriteFile,  FW_DEFAULT);
    dictAppendWord(dp, "write-line", ficlWriteLine,  FW_DEFAULT);
    dictAppendWord(dp, "file-position", ficlFilePosition,  FW_DEFAULT);
    dictAppendWord(dp, "file-size", ficlFileSize,  FW_DEFAULT);
    dictAppendWord(dp, "reposition-file", ficlRepositionFile,  FW_DEFAULT);
    dictAppendWord(dp, "file-status", ficlFileStatus,  FW_DEFAULT);
    dictAppendWord(dp, "flush-file", ficlFlushFile,  FW_DEFAULT);

    dictAppendWord(dp, "delete-file", ficlDeleteFile,  FW_DEFAULT);
    dictAppendWord(dp, "rename-file", ficlRenameFile,  FW_DEFAULT);

#ifdef FICL_HAVE_FTRUNCATE
    dictAppendWord(dp, "resize-file", ficlResizeFile,  FW_DEFAULT);

    ficlSetEnv(pSys, "file", FICL_TRUE);
    ficlSetEnv(pSys, "file-ext", FICL_TRUE);
#endif /* FICL_HAVE_FTRUNCATE */
#else
    (void)pSys;
#endif /* FICL_WANT_FILE */
}