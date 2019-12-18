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
typedef  size_t U64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const* const) ; 
 int /*<<< orphan*/  DISPLAYUPDATE (int,char*,char const* const) ; 
 int /*<<< orphan*/  RETURN_ERROR_INT (int,char*,...) ; 
 size_t UTIL_FILESIZE_UNKNOWN ; 
 size_t UTIL_getFileSize (char const* const) ; 
 scalar_t__ UTIL_isDirectory (char const* const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int BMK_loadFiles(void* buffer, size_t bufferSize,
                         size_t* fileSizes,
                         const char* const * fileNamesTable, unsigned nbFiles,
                         int displayLevel)
{
    size_t pos = 0, totalSize = 0;
    unsigned n;
    for (n=0; n<nbFiles; n++) {
        U64 fileSize = UTIL_getFileSize(fileNamesTable[n]);  /* last file may be shortened */
        if (UTIL_isDirectory(fileNamesTable[n])) {
            DISPLAYLEVEL(2, "Ignoring %s directory...       \n", fileNamesTable[n]);
            fileSizes[n] = 0;
            continue;
        }
        if (fileSize == UTIL_FILESIZE_UNKNOWN) {
            DISPLAYLEVEL(2, "Cannot evaluate size of %s, ignoring ... \n", fileNamesTable[n]);
            fileSizes[n] = 0;
            continue;
        }
        {   FILE* const f = fopen(fileNamesTable[n], "rb");
            if (f==NULL) RETURN_ERROR_INT(10, "impossible to open file %s", fileNamesTable[n]);
            DISPLAYUPDATE(2, "Loading %s...       \r", fileNamesTable[n]);
            if (fileSize > bufferSize-pos) fileSize = bufferSize-pos, nbFiles=n;   /* buffer too small - stop after this file */
            {   size_t const readSize = fread(((char*)buffer)+pos, 1, (size_t)fileSize, f);
                if (readSize != (size_t)fileSize) RETURN_ERROR_INT(11, "could not read %s", fileNamesTable[n]);
                pos += readSize;
            }
            fileSizes[n] = (size_t)fileSize;
            totalSize += (size_t)fileSize;
            fclose(f);
    }   }

    if (totalSize == 0) RETURN_ERROR_INT(12, "no data to bench");
    return 0;
}