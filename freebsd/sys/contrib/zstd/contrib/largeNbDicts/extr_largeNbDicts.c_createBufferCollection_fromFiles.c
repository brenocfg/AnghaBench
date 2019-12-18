#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** slicePtrs; size_t* capacities; unsigned int nbSlices; } ;
typedef  TYPE_1__ slice_collection_t ;
struct TYPE_6__ {void* ptr; size_t capacity; size_t size; } ;
typedef  TYPE_2__ buffer_t ;
struct TYPE_7__ {TYPE_1__ slices; TYPE_2__ buffer; } ;
typedef  TYPE_3__ buffer_collection_t ;
typedef  scalar_t__ U64 ;

/* Variables and functions */
 scalar_t__ const BENCH_SIZE_MAX ; 
 scalar_t__ const UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ UTIL_getTotalFileSize (char const* const*,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int loadFiles (void* const,size_t const,size_t* const,char const* const*,unsigned int) ; 
 void* malloc (size_t const) ; 

__attribute__((used)) static buffer_collection_t
createBufferCollection_fromFiles(const char* const * fileNamesTable, unsigned nbFiles)
{
    U64 const totalSizeToLoad = UTIL_getTotalFileSize(fileNamesTable, nbFiles);
    assert(totalSizeToLoad != UTIL_FILESIZE_UNKNOWN);
    assert(totalSizeToLoad <= BENCH_SIZE_MAX);
    size_t const loadedSize = (size_t)totalSizeToLoad;
    assert(loadedSize > 0);
    void* const srcBuffer = malloc(loadedSize);
    assert(srcBuffer != NULL);

    assert(nbFiles > 0);
    size_t* const fileSizes = (size_t*)calloc(nbFiles, sizeof(*fileSizes));
    assert(fileSizes != NULL);

    /* Load input buffer */
    int const errorCode = loadFiles(srcBuffer, loadedSize,
                                    fileSizes,
                                    fileNamesTable, nbFiles);
    assert(errorCode == 0);

    void** sliceTable = (void**)malloc(nbFiles * sizeof(*sliceTable));
    assert(sliceTable != NULL);

    char* const ptr = (char*)srcBuffer;
    size_t pos = 0;
    unsigned fileNb = 0;
    for ( ; (pos < loadedSize) && (fileNb < nbFiles); fileNb++) {
        sliceTable[fileNb] = ptr + pos;
        pos += fileSizes[fileNb];
    }
    assert(pos == loadedSize);
    assert(fileNb == nbFiles);


    buffer_t buffer;
    buffer.ptr = srcBuffer;
    buffer.capacity = loadedSize;
    buffer.size = loadedSize;

    slice_collection_t slices;
    slices.slicePtrs = sliceTable;
    slices.capacities = fileSizes;
    slices.nbSlices = nbFiles;

    buffer_collection_t bc;
    bc.buffer = buffer;
    bc.slices = slices;
    return bc;
}