#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt64 ;
typedef  size_t UInt32 ;
struct TYPE_13__ {scalar_t__* Vals; } ;
struct TYPE_12__ {int* FoCodersOffsets; scalar_t__* FoToMainUnpackSizeIndex; size_t* FoToCoderUnpackSizes; TYPE_7__ FolderCRCs; scalar_t__* FoStartPackStreamIndex; scalar_t__ PackPositions; int /*<<< orphan*/ * CoderUnpackSizes; int /*<<< orphan*/ * CodersData; } ;
struct TYPE_11__ {int Size; int /*<<< orphan*/  const* Data; } ;
struct TYPE_10__ {scalar_t__ UnpackStream; } ;
typedef  int /*<<< orphan*/  SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  TYPE_1__ CSzFolder ;
typedef  TYPE_2__ CSzData ;
typedef  TYPE_3__ CSzAr ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ CrcCalc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_CRC ; 
 scalar_t__ SZ_ERROR_FAIL ; 
 scalar_t__ SZ_OK ; 
 size_t SzAr_GetFolderUnpackSize (TYPE_3__ const*,size_t) ; 
 scalar_t__ SzBitWithVals_Check (TYPE_7__*,size_t) ; 
 scalar_t__ SzFolder_Decode2 (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ SzGetNextFolderItem (TYPE_1__*,TYPE_2__*) ; 

SRes SzAr_DecodeFolder(const CSzAr *p, UInt32 folderIndex,
    ILookInStream *inStream, UInt64 startPos,
    Byte *outBuffer, size_t outSize,
    ISzAllocPtr allocMain)
{
  SRes res;
  CSzFolder folder;
  CSzData sd;
  
  const Byte *data = p->CodersData + p->FoCodersOffsets[folderIndex];
  sd.Data = data;
  sd.Size = p->FoCodersOffsets[(size_t)folderIndex + 1] - p->FoCodersOffsets[folderIndex];
  
  res = SzGetNextFolderItem(&folder, &sd);
  
  if (res != SZ_OK)
    return res;

  if (sd.Size != 0
      || folder.UnpackStream != p->FoToMainUnpackSizeIndex[folderIndex]
      || outSize != SzAr_GetFolderUnpackSize(p, folderIndex))
    return SZ_ERROR_FAIL;
  {
    unsigned i;
    Byte *tempBuf[3] = { 0, 0, 0};

    res = SzFolder_Decode2(&folder, data,
        &p->CoderUnpackSizes[p->FoToCoderUnpackSizes[folderIndex]],
        p->PackPositions + p->FoStartPackStreamIndex[folderIndex],
        inStream, startPos,
        outBuffer, (SizeT)outSize, allocMain, tempBuf);
    
    for (i = 0; i < 3; i++)
      ISzAlloc_Free(allocMain, tempBuf[i]);

    if (res == SZ_OK)
      if (SzBitWithVals_Check(&p->FolderCRCs, folderIndex))
        if (CrcCalc(outBuffer, outSize) != p->FolderCRCs.Vals[folderIndex])
          res = SZ_ERROR_CRC;

    return res;
  }
}