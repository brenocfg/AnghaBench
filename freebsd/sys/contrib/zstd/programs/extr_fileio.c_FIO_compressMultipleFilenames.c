#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dstFile; } ;
typedef  TYPE_1__ cRess_t ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  FIO_checkFilenameCollisions (char const**,unsigned int) ; 
 int FIO_compressFilename_srcFile (int /*<<< orphan*/ * const,TYPE_1__,char const* const,char const* const,int) ; 
 TYPE_1__ FIO_createCResources (int /*<<< orphan*/ * const,char const*,int,int /*<<< orphan*/ ) ; 
 char* FIO_determineCompressedName (char const* const,char const*,char const*) ; 
 int /*<<< orphan*/  FIO_freeCResources (TYPE_1__) ; 
 int /*<<< orphan*/ * FIO_openDstFile (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int FIO_compressMultipleFilenames(FIO_prefs_t* const prefs,
                                  const char** inFileNamesTable, unsigned nbFiles,
                                  const char* outDirName,
                                  const char* outFileName, const char* suffix,
                                  const char* dictFileName, int compressionLevel,
                                  ZSTD_compressionParameters comprParams)
{
    int error = 0;
    cRess_t ress = FIO_createCResources(prefs, dictFileName, compressionLevel, comprParams);

    /* init */
    assert(outFileName != NULL || suffix != NULL);
    if (outFileName != NULL) {   /* output into a single destination (stdout typically) */
        ress.dstFile = FIO_openDstFile(prefs, NULL, outFileName);
        if (ress.dstFile == NULL) {  /* could not open outFileName */
            error = 1;
        } else {
            unsigned u;
            for (u=0; u<nbFiles; u++)
                error |= FIO_compressFilename_srcFile(prefs, ress, outFileName, inFileNamesTable[u], compressionLevel);
            if (fclose(ress.dstFile))
                EXM_THROW(29, "Write error (%s) : cannot properly close %s",
                            strerror(errno), outFileName);
            ress.dstFile = NULL;
        }
    } else {
        unsigned u;
        for (u=0; u<nbFiles; u++) {
            const char* const srcFileName = inFileNamesTable[u];
            const char* const dstFileName = FIO_determineCompressedName(srcFileName, outDirName, suffix);  /* cannot fail */
            error |= FIO_compressFilename_srcFile(prefs, ress, dstFileName, srcFileName, compressionLevel);
        }
        if (outDirName)
            FIO_checkFilenameCollisions(inFileNamesTable ,nbFiles);
    }

    FIO_freeCResources(ress);
    return error;
}