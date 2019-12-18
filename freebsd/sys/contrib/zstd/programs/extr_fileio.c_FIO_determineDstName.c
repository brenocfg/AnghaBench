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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 char* FIO_createFilename_fromOutDir (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcmp (char const*,char const* const) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 char** suffixList ; 
 int /*<<< orphan*/  suffixListStr ; 

__attribute__((used)) static const char*
FIO_determineDstName(const char* srcFileName, const char* outDirName)
{
    static size_t dfnbCapacity = 0;
    static char* dstFileNameBuffer = NULL;   /* using static allocation : this function cannot be multi-threaded */
    size_t dstFileNameEndPos;
    char* outDirFilename = NULL;
    const char* dstSuffix = "";
    size_t dstSuffixLen = 0;

    size_t sfnSize = strlen(srcFileName);

    size_t srcSuffixLen;
    const char* const srcSuffix = strrchr(srcFileName, '.');
    if (srcSuffix == NULL) {
        DISPLAYLEVEL(1,
            "zstd: %s: unknown suffix (%s expected). "
            "Can't derive the output file name. "
            "Specify it with -o dstFileName. Ignoring.\n",
            srcFileName, suffixListStr);
        return NULL;
    }
    srcSuffixLen = strlen(srcSuffix);

    {
        const char** matchedSuffixPtr;
        for (matchedSuffixPtr = suffixList; *matchedSuffixPtr != NULL; matchedSuffixPtr++) {
            if (!strcmp(*matchedSuffixPtr, srcSuffix)) {
                break;
            }
        }

        /* check suffix is authorized */
        if (sfnSize <= srcSuffixLen || *matchedSuffixPtr == NULL) {
            DISPLAYLEVEL(1,
                "zstd: %s: unknown suffix (%s expected). "
                "Can't derive the output file name. "
                "Specify it with -o dstFileName. Ignoring.\n",
                srcFileName, suffixListStr);
            return NULL;
        }

        if ((*matchedSuffixPtr)[1] == 't') {
            dstSuffix = ".tar";
            dstSuffixLen = strlen(dstSuffix);
        }
    }

    if (outDirName) {
        outDirFilename = FIO_createFilename_fromOutDir(srcFileName, outDirName, 0);
        sfnSize = strlen(outDirFilename);
        assert(outDirFilename != NULL);
    }

    if (dfnbCapacity+srcSuffixLen <= sfnSize+1+dstSuffixLen) {
        /* allocate enough space to write dstFilename into it */
        free(dstFileNameBuffer);
        dfnbCapacity = sfnSize + 20;
        dstFileNameBuffer = (char*)malloc(dfnbCapacity);
        if (dstFileNameBuffer==NULL)
            EXM_THROW(74, "%s : not enough memory for dstFileName",
                      strerror(errno));
    }

    /* return dst name == src name truncated from suffix */
    assert(dstFileNameBuffer != NULL);
    dstFileNameEndPos = sfnSize - srcSuffixLen;
    if (outDirFilename) {
        memcpy(dstFileNameBuffer, outDirFilename, dstFileNameEndPos);
        free(outDirFilename);
    } else {
        memcpy(dstFileNameBuffer, srcFileName, dstFileNameEndPos);
    }

    /* The short tar extensions tzst, tgz, txz and tlz4 files should have "tar"
     * extension on decompression. Also writes terminating null. */
    strcpy(dstFileNameBuffer + dstFileNameEndPos, dstSuffix);
    return dstFileNameBuffer;

    /* note : dstFileNameBuffer memory is not going to be free */
}