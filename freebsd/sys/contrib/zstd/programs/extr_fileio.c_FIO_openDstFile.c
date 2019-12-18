#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int displayLevel; } ;
struct TYPE_4__ {int sparseFileSupport; int /*<<< orphan*/  overwrite; scalar_t__ testMode; } ;
typedef  TYPE_1__ FIO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int EOF ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*) ; 
 int /*<<< orphan*/  FIO_remove (char const*) ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ UTIL_isRegularFile (char const*) ; 
 scalar_t__ UTIL_isSameFile (char const*,char const*) ; 
 int ZSTD_SPARSE_DEFAULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmod (char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 TYPE_2__ g_display_prefs ; 
 int getchar () ; 
 int /*<<< orphan*/  nulmark ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE*
FIO_openDstFile(FIO_prefs_t* const prefs,
          const char* srcFileName, const char* dstFileName)
{
    if (prefs->testMode) return NULL;  /* do not open file in test mode */

    assert(dstFileName != NULL);
    if (!strcmp (dstFileName, stdoutmark)) {
        DISPLAYLEVEL(4,"Using stdout for output \n");
        SET_BINARY_MODE(stdout);
        if (prefs->sparseFileSupport == 1) {
            prefs->sparseFileSupport = 0;
            DISPLAYLEVEL(4, "Sparse File Support is automatically disabled on stdout ; try --sparse \n");
        }
        return stdout;
    }

    /* ensure dst is not the same as src */
    if (srcFileName != NULL && UTIL_isSameFile(srcFileName, dstFileName)) {
        DISPLAYLEVEL(1, "zstd: Refusing to open an output file which will overwrite the input file \n");
        return NULL;
    }

    if (prefs->sparseFileSupport == 1) {
        prefs->sparseFileSupport = ZSTD_SPARSE_DEFAULT;
    }

    if (UTIL_isRegularFile(dstFileName)) {
        /* Check if destination file already exists */
        FILE* const fCheck = fopen( dstFileName, "rb" );
#if !defined(_WIN32)
        /* this test does not work on Windows :
         * `NUL` and `nul` are detected as regular files */
        if (!strcmp(dstFileName, nulmark)) {
            EXM_THROW(40, "%s is unexpectedly categorized as a regular file",
                        dstFileName);
        }
#endif
        if (fCheck != NULL) {  /* dst file exists, authorization prompt */
            fclose(fCheck);
            if (!prefs->overwrite) {
                if (g_display_prefs.displayLevel <= 1) {
                    /* No interaction possible */
                    DISPLAY("zstd: %s already exists; not overwritten  \n",
                            dstFileName);
                    return NULL;
                }
                DISPLAY("zstd: %s already exists; overwrite (y/N) ? ",
                        dstFileName);
                {   int ch = getchar();
                    if ((ch!='Y') && (ch!='y')) {
                        DISPLAY("    not overwritten  \n");
                        return NULL;
                    }
                    /* flush rest of input line */
                    while ((ch!=EOF) && (ch!='\n')) ch = getchar();
            }   }
            /* need to unlink */
            FIO_remove(dstFileName);
    }   }

    {   FILE* const f = fopen( dstFileName, "wb" );
        if (f == NULL) {
            DISPLAYLEVEL(1, "zstd: %s: %s\n", dstFileName, strerror(errno));
        } else if(srcFileName != NULL && strcmp (srcFileName, stdinmark)) {
            chmod(dstFileName, 00600);
        }
        return f;
    }
}