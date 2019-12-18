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
typedef  int /*<<< orphan*/  stat_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dstFile; int /*<<< orphan*/ * srcFile; } ;
typedef  TYPE_1__ cRess_t ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,...) ; 
 int FIO_compressFilename_internal (int /*<<< orphan*/ * const,TYPE_1__,char const*,char const*,int) ; 
 int /*<<< orphan*/ * FIO_openDstFile (int /*<<< orphan*/ * const,char const*,char const*) ; 
 int /*<<< orphan*/  FIO_remove (char const*) ; 
 scalar_t__ UTIL_getFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTIL_setFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addHandler (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearHandler () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  nulmark ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FIO_compressFilename_dstFile(FIO_prefs_t* const prefs,
                                        cRess_t ress,
                                        const char* dstFileName,
                                        const char* srcFileName,
                                        int compressionLevel)
{
    int closeDstFile = 0;
    int result;
    stat_t statbuf;
    int transfer_permissions = 0;
    assert(ress.srcFile != NULL);
    if (ress.dstFile == NULL) {
        closeDstFile = 1;
        DISPLAYLEVEL(6, "FIO_compressFilename_dstFile: opening dst: %s", dstFileName);
        ress.dstFile = FIO_openDstFile(prefs, srcFileName, dstFileName);
        if (ress.dstFile==NULL) return 1;  /* could not open dstFileName */
        /* Must only be added after FIO_openDstFile() succeeds.
         * Otherwise we may delete the destination file if it already exists,
         * and the user presses Ctrl-C when asked if they wish to overwrite.
         */
        addHandler(dstFileName);

        if ( strcmp (srcFileName, stdinmark)
          && UTIL_getFileStat(srcFileName, &statbuf))
            transfer_permissions = 1;
    }

    result = FIO_compressFilename_internal(prefs, ress, dstFileName, srcFileName, compressionLevel);

    if (closeDstFile) {
        FILE* const dstFile = ress.dstFile;
        ress.dstFile = NULL;

        clearHandler();

        if (fclose(dstFile)) { /* error closing dstFile */
            DISPLAYLEVEL(1, "zstd: %s: %s \n", dstFileName, strerror(errno));
            result=1;
        }
        if ( (result != 0)  /* operation failure */
          && strcmp(dstFileName, nulmark)     /* special case : don't remove() /dev/null */
          && strcmp(dstFileName, stdoutmark)  /* special case : don't remove() stdout */
          ) {
            FIO_remove(dstFileName); /* remove compression artefact; note don't do anything special if remove() fails */
        } else if ( strcmp(dstFileName, stdoutmark)
                 && strcmp(dstFileName, nulmark)
                 && transfer_permissions) {
            UTIL_setFileStat(dstFileName, &statbuf);
        }
    }

    return result;
}