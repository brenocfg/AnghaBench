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
typedef  size_t UInt64 ;
typedef  size_t UInt32 ;
struct TYPE_5__ {scalar_t__* Vals; } ;
struct TYPE_4__ {size_t* FileToFolder; size_t* UnpackPositions; size_t* FolderToFile; TYPE_2__ CRCs; int /*<<< orphan*/  dataPos; int /*<<< orphan*/  db; } ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  TYPE_1__ CSzArEx ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ CrcCalc (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_CRC ; 
 scalar_t__ SZ_ERROR_FAIL ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ SzAr_DecodeFolder (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t SzAr_GetFolderUnpackSize (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ SzBitWithVals_Check (TYPE_2__*,size_t) ; 

SRes SzArEx_Extract(
    const CSzArEx *p,
    ILookInStream *inStream,
    UInt32 fileIndex,
    UInt32 *blockIndex,
    Byte **tempBuf,
    size_t *outBufferSize,
    size_t *offset,
    size_t *outSizeProcessed,
    ISzAllocPtr allocMain,
    ISzAllocPtr allocTemp)
{
  UInt32 folderIndex = p->FileToFolder[fileIndex];
  SRes res = SZ_OK;
  
  *offset = 0;
  *outSizeProcessed = 0;
  
  if (folderIndex == (UInt32)-1)
  {
    ISzAlloc_Free(allocMain, *tempBuf);
    *blockIndex = folderIndex;
    *tempBuf = NULL;
    *outBufferSize = 0;
    return SZ_OK;
  }

  if (*tempBuf == NULL || *blockIndex != folderIndex)
  {
    UInt64 unpackSizeSpec = SzAr_GetFolderUnpackSize(&p->db, folderIndex);
    /*
    UInt64 unpackSizeSpec =
        p->UnpackPositions[p->FolderToFile[(size_t)folderIndex + 1]] -
        p->UnpackPositions[p->FolderToFile[folderIndex]];
    */
    size_t unpackSize = (size_t)unpackSizeSpec;

    if (unpackSize != unpackSizeSpec)
      return SZ_ERROR_MEM;
    *blockIndex = folderIndex;
    ISzAlloc_Free(allocMain, *tempBuf);
    *tempBuf = NULL;
    
    if (res == SZ_OK)
    {
      *outBufferSize = unpackSize;
      if (unpackSize != 0)
      {
        *tempBuf = (Byte *)ISzAlloc_Alloc(allocMain, unpackSize);
        if (*tempBuf == NULL)
          res = SZ_ERROR_MEM;
      }
  
      if (res == SZ_OK)
      {
        res = SzAr_DecodeFolder(&p->db, folderIndex,
            inStream, p->dataPos, *tempBuf, unpackSize, allocTemp);
      }
    }
  }

  if (res == SZ_OK)
  {
    UInt64 unpackPos = p->UnpackPositions[fileIndex];
    *offset = (size_t)(unpackPos - p->UnpackPositions[p->FolderToFile[folderIndex]]);
    *outSizeProcessed = (size_t)(p->UnpackPositions[(size_t)fileIndex + 1] - unpackPos);
    if (*offset + *outSizeProcessed > *outBufferSize)
      return SZ_ERROR_FAIL;
    if (SzBitWithVals_Check(&p->CRCs, fileIndex))
      if (CrcCalc(*tempBuf + *offset, *outSizeProcessed) != p->CRCs.Vals[fileIndex])
        res = SZ_ERROR_CRC;
  }

  return res;
}